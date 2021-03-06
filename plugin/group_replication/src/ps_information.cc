/* Copyright (c) 2015, 2021, Oracle and/or its affiliates.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is also distributed with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have included with MySQL.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA */

#include <string>

#include "mutex_lock.h"
#include "plugin/group_replication/include/member_info.h"
#include "plugin/group_replication/include/plugin.h"
#include "plugin/group_replication/include/ps_information.h"

using std::string;

bool get_group_members_info(
    uint index, const GROUP_REPLICATION_GROUP_MEMBERS_CALLBACKS &callbacks,
    Group_member_info_manager_interface *group_member_manager,
    Gcs_operations *gcs_module, char *channel_name) {
  if (channel_name != nullptr) {
    callbacks.set_channel_name(callbacks.context, *channel_name,
                               strlen(channel_name));
  }

  /*
   This case means that the plugin has never been initialized...
   and one would not be able to extract information
   */
  if (group_member_manager == nullptr) {
    const char *member_state = Group_member_info::get_member_status_string(
        Group_member_info::MEMBER_OFFLINE);
    callbacks.set_member_state(callbacks.context, *member_state,
                               strlen(member_state));
    return false;
  }

  size_t number_of_members = group_member_manager->get_number_of_members();
  if (index >= number_of_members) {
    /* purecov: begin inspected */
    if (index != 0) {
      // No members on view.
      return true;
    }
    /* purecov: end */
  }

  Group_member_info *member_info = nullptr;
  /*
    If the local member is already OFFLINE but still has the previous
    membership because is waiting for the leave view, do not report
    the other members.
  */
  if (local_member_info != nullptr &&
      local_member_info->get_recovery_status() ==
          Group_member_info::MEMBER_OFFLINE) {
    member_info = group_member_manager->get_group_member_info(
        local_member_info->get_uuid());
  } else {
    member_info = group_member_manager->get_group_member_info_by_index(index);
  }

  if (member_info == nullptr)  // The requested member is not managed...
  {
    return true; /* purecov: inspected */
  }

  // Get info from view.
  std::string uuid(member_info->get_uuid());
  callbacks.set_member_id(callbacks.context, *uuid.c_str(), uuid.length());

  std::string hostname(member_info->get_hostname());
  callbacks.set_member_host(callbacks.context, *hostname.c_str(),
                            hostname.length());

  callbacks.set_member_port(callbacks.context, member_info->get_port());

  const char *member_state;
  const char *member_role = member_info->get_member_role_string();
  std::string member_version =
      (member_info->get_recovery_status() != Group_member_info::MEMBER_OFFLINE)
          ? member_info->get_member_version().get_version_string()
          : "";

  // override the state if we think it is unreachable
  if (!member_info->is_unreachable())
    member_state = Group_member_info::get_member_status_string(
        member_info->get_recovery_status());
  else
    member_state = Group_member_info::get_member_status_string(
        Group_member_info::MEMBER_UNREACHABLE);

  callbacks.set_member_state(callbacks.context, *member_state,
                             strlen(member_state));

  callbacks.set_member_role(callbacks.context, *member_role,
                            strlen(member_role));

  callbacks.set_member_version(callbacks.context, *member_version.c_str(),
                               member_version.length());

  enum_transport_protocol incoming_connection_protocol_value = INVALID_PROTOCOL;
  if (gcs_module == nullptr || (local_member_info->get_recovery_status() ==
                                Group_member_info::MEMBER_OFFLINE)) {
    // use the value that is present in the variable
    incoming_connection_protocol_value =
        static_cast<enum_transport_protocol>(get_communication_stack_var());
  } else {
    incoming_connection_protocol_value =
        gcs_module->get_current_incoming_connections_protocol();
  }

  const char *incoming_connection_protocol =
      Communication_stack_to_string::to_string(
          incoming_connection_protocol_value);
  callbacks.set_member_incoming_communication_protocol(
      callbacks.context, *incoming_connection_protocol,
      strlen(incoming_connection_protocol));

  delete member_info;

  return false;
}

bool get_group_member_stats(
    uint index, const GROUP_REPLICATION_GROUP_MEMBER_STATS_CALLBACKS &callbacks,
    Group_member_info_manager_interface *group_member_manager,
    Gcs_operations *gcs_module, char *channel_name) {
  if (channel_name != nullptr) {
    callbacks.set_channel_name(callbacks.context, *channel_name,
                               strlen(channel_name));
  }

  /*
   This case means that the plugin has never been initialized...
   and one would not be able to extract information
   */
  if (group_member_manager == nullptr) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_members_info, leave at pos 1");
    return false;
  }

  Group_member_info *member_info = nullptr;
  /*
    If the local member is already OFFLINE but still has the previous
    membership because is waiting for the leave view, do not report
    the other members.
  */
  if (local_member_info != nullptr &&
      local_member_info->get_recovery_status() ==
          Group_member_info::MEMBER_OFFLINE) {
    member_info = group_member_manager->get_group_member_info(
        local_member_info->get_uuid());
  } else {
    member_info = group_member_manager->get_group_member_info_by_index(index);
  }

  if (member_info == nullptr)  // The requested member is not managed...
  {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_members_info, leave at pos 2");
    return true; /* purecov: inspected */
  }

  std::string uuid(member_info->get_uuid());
  callbacks.set_member_id(callbacks.context, *uuid.c_str(), uuid.length());

  if (nullptr == local_member_info ||
      local_member_info->get_recovery_status() ==
          Group_member_info::MEMBER_OFFLINE) {
    delete member_info;
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_members_info, leave at pos 3");
    return false;
  }

  // Retrieve view information
  Gcs_view *view = gcs_module->get_current_view();
  if (view != nullptr) {
    const char *view_id_representation =
        view->get_view_id().get_representation().c_str();
    callbacks.set_view_id(callbacks.context, *view_id_representation,
                          strlen(view_id_representation));
    delete view;
  }

  DBUG_EXECUTE_IF("group_replication_get_group_member_stats", {
    const char act[] =
        "now signal signal.reached_get_group_member_stats "
        "wait_for signal.resume_get_group_member_stats";
    assert(!debug_sync_set_action(current_thd, STRING_WITH_LEN(act)));
  });
  // Check if the group replication has started and a valid certifier exists
  MUTEX_LOCK(lock, get_plugin_applier_module_lock());
  Pipeline_member_stats *pipeline_stats = nullptr;
  bool ret = (!get_plugin_is_stopping() && applier_module != nullptr);
  if (!ret) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_members_info, ret is false at pos 1");
  }

  DBUG_SIGNAL_WAIT_FOR(
      current_thd, "group_replication_status_when_terminal_applier",
      "reach_get_member_status_sync", "end_get_member_status_sync");
  ret = ret && plugin_is_group_replication_running();
  DBUG_SIGNAL_WAIT_FOR(current_thd, "group_replication_stats_when_rejoin",
                       "reach_rejoin_stats_sync", "end_rejoin_stats_sync");
  if (!ret) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_members_info, ret is false at pos 2");
  }
  ret =
      ret &&
      (pipeline_stats =
           ((local_member_info && !local_member_info->get_uuid().compare(uuid))
                ? applier_module->get_local_pipeline_stats()
                : applier_module->get_flow_control_module()->get_pipeline_stats(
                      member_info->get_gcs_member_id().get_member_id()))) !=
          nullptr;
  if (ret) {
    std::string last_conflict_free_transaction;
    pipeline_stats->get_transaction_last_conflict_free(
        last_conflict_free_transaction);
    callbacks.set_last_conflict_free_transaction(
        callbacks.context, *last_conflict_free_transaction.c_str(),
        last_conflict_free_transaction.length());

    std::string transaction_committed_all_members;
    pipeline_stats->get_transaction_committed_all_members(
        transaction_committed_all_members);
    callbacks.set_transactions_committed(
        callbacks.context, *transaction_committed_all_members.c_str(),
        transaction_committed_all_members.length());

    /* certification related data */
    callbacks.set_transactions_conflicts_detected(
        callbacks.context,
        pipeline_stats->get_transactions_negative_certified());
    callbacks.set_transactions_certified(
        callbacks.context, pipeline_stats->get_transactions_certified());
    callbacks.set_transactions_rows_in_validation(
        callbacks.context, pipeline_stats->get_transactions_rows_validating());
    callbacks.set_transactions_in_queue(
        callbacks.context,
        pipeline_stats->get_transactions_waiting_certification());

    /* applier information */
    callbacks.set_transactions_remote_applier_queue(
        callbacks.context, pipeline_stats->get_transactions_waiting_apply());
    callbacks.set_transactions_remote_applied(
        callbacks.context, pipeline_stats->get_transactions_applied());

    /* local member information */
    callbacks.set_transactions_local_proposed(
        callbacks.context, pipeline_stats->get_transactions_local());
    callbacks.set_transactions_local_rollback(
        callbacks.context, pipeline_stats->get_transactions_local_rollback());

    /* clean-up */
    delete pipeline_stats;
  } else {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_member_stats, pipeline_stats is not set");
  }

  delete member_info;

  return false;
}

bool get_group_flow_control_stats(
    uint index, const GROUP_REPLICATION_FLOW_CONTROL_STATS_CALLBACKS &callbacks,
    Group_member_info_manager_interface *group_member_manager,
    char *channel_name) {
  /*
   This case means that the plugin has never been initialized...
   and one would not be able to extract information
   */
  if (group_member_manager == nullptr) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_flow_control_stats, leave at pos 1");
    return false;
  }

  Group_member_info *member_info = nullptr;
  if (local_member_info) {
    member_info = group_member_manager->get_group_member_info(
        local_member_info->get_uuid());
  }

  if (member_info == nullptr)  // The requested member is not managed...
  {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_flow_control_stats, leave at pos 2");
    return true; /* purecov: inspected */
  }

  if (local_member_info->get_recovery_status() ==
      Group_member_info::MEMBER_OFFLINE) {
    delete member_info;
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_flow_control_stats, leave at pos 3");
    return false;
  }

  // Check if the group replication has started and a valid certifier exists
  MUTEX_LOCK(lock, get_plugin_applier_module_lock());
  bool ret = (!get_plugin_is_stopping() && applier_module != nullptr);
  if (!ret) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_flow_control_stats, ret is false at pos 1");
  }

  ret = ret && plugin_is_group_replication_running();
  if (!ret) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_flow_control_stats, ret is false at pos 2");
  } else {
    std::string hostname(member_info->get_hostname());
    callbacks.set_member_host(callbacks.context, *hostname.c_str(),
                              hostname.length());

    callbacks.set_member_port(callbacks.context, member_info->get_port());

    Flow_control_module *flow = applier_module->get_flow_control_module();

    /* local member information */
    callbacks.set_stat_less_than_10(callbacks.context,
                                    flow->get_flow_control_stat(0));
    callbacks.set_stat_between_10_and_20(callbacks.context,
                                         flow->get_flow_control_stat(1));
    callbacks.set_stat_between_20_and_30(callbacks.context,
                                         flow->get_flow_control_stat(2));
    callbacks.set_stat_between_30_and_40(callbacks.context,
                                         flow->get_flow_control_stat(3));
    callbacks.set_stat_between_40_and_50(callbacks.context,
                                         flow->get_flow_control_stat(4));
    callbacks.set_stat_between_50_and_100(callbacks.context,
                                          flow->get_flow_control_stat(5));
    callbacks.set_stat_between_100_and_200(callbacks.context,
                                           flow->get_flow_control_stat(6));
    callbacks.set_stat_between_200_and_300(callbacks.context,
                                           flow->get_flow_control_stat(7));
    callbacks.set_stat_between_300_and_400(callbacks.context,
                                           flow->get_flow_control_stat(8));
    callbacks.set_stat_between_400_and_500(callbacks.context,
                                           flow->get_flow_control_stat(9));
    callbacks.set_stat_between_500_and_1000(callbacks.context,
                                            flow->get_flow_control_stat(10));
    callbacks.set_stat_between_1000_and_2000(callbacks.context,
                                             flow->get_flow_control_stat(11));
    callbacks.set_stat_between_2000_and_3000(callbacks.context,
                                             flow->get_flow_control_stat(12));
    callbacks.set_stat_between_3000_and_4000(callbacks.context,
                                             flow->get_flow_control_stat(13));
    callbacks.set_stat_between_4000_and_5000(callbacks.context,
                                             flow->get_flow_control_stat(14));
    callbacks.set_stat_more_than_5000(callbacks.context,
                                      flow->get_flow_control_stat(15));
  }

  delete member_info;

  return false;
}

bool get_group_mgr_stats(
    uint index, const GROUP_REPLICATION_MGR_STATS_CALLBACKS &callbacks,
    Group_member_info_manager_interface *group_member_manager,
    char *channel_name) {
  /*
   This case means that the plugin has never been initialized...
   and one would not be able to extract information
   */
  if (group_member_manager == nullptr) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_mgr_stats, leave at pos 1");
    return false;
  }

  Group_member_info *member_info = nullptr;
  if (local_member_info) {
    member_info = group_member_manager->get_group_member_info(
        local_member_info->get_uuid());
  }

  if (member_info == nullptr)  // The requested member is not managed...
  {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_mgr_stats, leave at pos 2");
    return true; /* purecov: inspected */
  }

  if (local_member_info->get_recovery_status() ==
      Group_member_info::MEMBER_OFFLINE) {
    delete member_info;
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_mgr_stats, leave at pos 3");
    return false;
  }

  // Check if the group replication has started and a valid certifier exists
  MUTEX_LOCK(lock, get_plugin_applier_module_lock());
  bool ret = (!get_plugin_is_stopping() && applier_module != nullptr);
  if (!ret) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_mgr_stats, ret is false at pos 1");
  }

  ret = ret && plugin_is_group_replication_running();
  if (!ret) {
    LogPluginErrMsg(INFORMATION_LEVEL, ER_LOG_PRINTF_MSG,
                    "get_group_mgr_stats, ret is false at pos 2");
  } else {
    std::string hostname(member_info->get_hostname());
    callbacks.set_member_host(callbacks.context, *hostname.c_str(),
                              hostname.length());

    callbacks.set_member_port(callbacks.context, member_info->get_port());

    long long unsigned int *mgr_stat = applier_module->get_mgr_stat();

    /* local member information */
    callbacks.set_stat_less_than_10(callbacks.context, mgr_stat[0]);
    callbacks.set_stat_between_10_and_20(callbacks.context, mgr_stat[1]);
    callbacks.set_stat_between_20_and_30(callbacks.context, mgr_stat[2]);
    callbacks.set_stat_between_30_and_40(callbacks.context, mgr_stat[3]);
    callbacks.set_stat_between_40_and_50(callbacks.context, mgr_stat[4]);
    callbacks.set_stat_between_50_and_60(callbacks.context, mgr_stat[5]);
    callbacks.set_stat_between_60_and_70(callbacks.context, mgr_stat[6]);
    callbacks.set_stat_between_70_and_80(callbacks.context, mgr_stat[7]);
    callbacks.set_stat_between_80_and_90(callbacks.context, mgr_stat[8]);
    callbacks.set_stat_between_90_and_100(callbacks.context, mgr_stat[9]);
    callbacks.set_stat_between_100_and_200(callbacks.context, mgr_stat[10]);
    callbacks.set_stat_between_200_and_300(callbacks.context, mgr_stat[11]);
    callbacks.set_stat_between_300_and_400(callbacks.context, mgr_stat[12]);
    callbacks.set_stat_between_400_and_500(callbacks.context, mgr_stat[13]);
    callbacks.set_stat_between_500_and_1000(callbacks.context, mgr_stat[14]);
    callbacks.set_stat_more_than_1000(callbacks.context, mgr_stat[15]);
  }

  delete member_info;

  return false;
}

bool get_connection_status(
    const GROUP_REPLICATION_CONNECTION_STATUS_CALLBACKS &callbacks,
    char *group_name_pointer, char *channel_name,
    bool is_group_replication_running) {
  if (channel_name != nullptr) {
    callbacks.set_channel_name(callbacks.context, *channel_name,
                               strlen(channel_name));
  }

  if (group_name_pointer != nullptr) {
    callbacks.set_group_name(callbacks.context, *group_name_pointer,
                             strlen(group_name_pointer));
    callbacks.set_source_uuid(callbacks.context, *group_name_pointer,
                              strlen(group_name_pointer));
  }

  callbacks.set_service_state(callbacks.context, is_group_replication_running);

  return false;
}
