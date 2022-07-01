/*
  Copyright (c) 2013, 2021, Oracle and/or its affiliates. All rights reserved.

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
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

/**
  @file storage/perfschema/table_replication_group_mgr_stats.cc
  Table replication_group_mgr_stat (implementation).
*/

#include "storage/perfschema/table_replication_group_mgr_stats.h"

#include <stddef.h>

#include "my_compiler.h"
#include "my_dbug.h"
#include "mysql/plugin_group_replication.h"
#include "sql/field.h"
#include "sql/log.h"
#include "sql/plugin_table.h"
#include "sql/rpl_group_replication.h"
#include "sql/table.h"
#include "storage/perfschema/pfs_instr.h"
#include "storage/perfschema/pfs_instr_class.h"
#include "storage/perfschema/table_helper.h"
#include "thr_lock.h"

/*
  Callbacks implementation for
  GROUP_REPLICATION_MGR_STATS_CALLBACKS.
*/

static void set_member_host(void *const context, const char &value,
                            size_t length) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  const size_t max = HOSTNAME_LENGTH;
  length = std::min(length, max);

  row->member_host_length = length;
  memcpy(row->member_host, &value, length);
}

static void set_member_port(void *const context, unsigned int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->member_port = value;
}

static void set_stat_less_than_10(void *const context,
                                  unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_less_than_10 = value;
}

static void set_stat_between_10_and_20(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_10_and_20 = value;
}

static void set_stat_between_20_and_30(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_20_and_30 = value;
}

static void set_stat_between_30_and_40(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_30_and_40 = value;
}

static void set_stat_between_40_and_50(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_40_and_50 = value;
}

static void set_stat_between_50_and_60(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_50_and_60 = value;
}

static void set_stat_between_60_and_70(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_60_and_70 = value;
}

static void set_stat_between_70_and_80(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_70_and_80 = value;
}

static void set_stat_between_80_and_90(void *const context,
                                       unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_80_and_90 = value;
}

static void set_stat_between_90_and_100(void *const context,
                                        unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_90_and_100 = value;
}

static void set_stat_between_100_and_200(void *const context,
                                         unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_100_and_200 = value;
}

static void set_stat_between_200_and_300(void *const context,
                                         unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_200_and_300 = value;
}

static void set_stat_between_300_and_400(void *const context,
                                         unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_300_and_400 = value;
}

static void set_stat_between_400_and_500(void *const context,
                                         unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_400_and_500 = value;
}

static void set_stat_between_500_and_1000(void *const context,
                                          unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_between_500_and_1000 = value;
}

static void set_stat_larger_than_1000(void *const context,
                                      unsigned long long int value) {
  struct st_row_group_mgr_stat *row =
      static_cast<struct st_row_group_mgr_stat *>(context);
  row->stat_more_than_1000 = value;
}

THR_LOCK table_replication_group_mgr_stats::m_table_lock;

Plugin_table table_replication_group_mgr_stats::m_table_def(
    /* Schema name */
    "performance_schema",
    /* Name */
    "replication_group_mgr_stats",
    /* Definition */
    "  MEMBER_HOST CHAR(255) CHARACTER SET ASCII not null,\n"
    "  MEMBER_PORT INTEGER,\n"
    "  less_than_10 BIGINT unsigned not null,\n"
    "  between_10_and_20 BIGINT unsigned not null,\n"
    "  between_20_and_30 BIGINT unsigned not null,\n"
    "  between_30_and_40 BIGINT unsigned not null,\n"
    "  between_40_and_50 BIGINT unsigned not null,\n"
    "  between_50_and_60 BIGINT unsigned not null,\n"
    "  between_60_and_70 BIGINT unsigned not null,\n"
    "  between_70_and_80 BIGINT unsigned not null,\n"
    "  between_80_and_90 BIGINT unsigned not null,\n"
    "  between_90_and_100 BIGINT unsigned not null,\n"
    "  between_100_and_200 BIGINT unsigned not null,\n"
    "  between_200_and_300 BIGINT unsigned not null,\n"
    "  between_300_and_400 BIGINT unsigned not null,\n"
    "  between_400_and_500 BIGINT unsigned not null,\n"
    "  between_5000_and_1000 BIGINT unsigned not null,\n"
    "  more_than_1000 BIGINT unsigned not null\n",
    /* Options */
    " ENGINE=PERFORMANCE_SCHEMA",
    /* Tablespace */
    nullptr);

PFS_engine_table_share table_replication_group_mgr_stats::m_share = {
    &pfs_readonly_acl,
    &table_replication_group_mgr_stats::create,
    nullptr, /* write_row */
    nullptr, /* delete_all_rows */
    table_replication_group_mgr_stats::get_row_count,
    sizeof(pos_t), /* ref length */
    &m_table_lock,
    &m_table_def,
    true, /* perpetual */
    PFS_engine_table_proxy(),
    {0},
    false /* m_in_purgatory */
};

PFS_engine_table *table_replication_group_mgr_stats::create(
    PFS_engine_table_share *) {
  return new table_replication_group_mgr_stats();
}

table_replication_group_mgr_stats::table_replication_group_mgr_stats()
    : PFS_engine_table(&m_share, &m_pos), m_pos(0), m_next_pos(0) {}

table_replication_group_mgr_stats::~table_replication_group_mgr_stats() =
    default;

void table_replication_group_mgr_stats::reset_position(void) {
  m_pos.m_index = 0;
  m_next_pos.m_index = 0;
}

ha_rows table_replication_group_mgr_stats::get_row_count() { return 1; }

int table_replication_group_mgr_stats::rnd_next(void) {
  if (!is_group_replication_plugin_loaded()) {
    return HA_ERR_END_OF_FILE;
  }

  for (m_pos.set_at(&m_next_pos); m_pos.m_index < get_row_count();
       m_pos.next()) {
    m_next_pos.set_after(&m_pos);
    return make_row(m_pos.m_index);
  }

  return HA_ERR_END_OF_FILE;
}

int table_replication_group_mgr_stats::rnd_pos(const void *pos) {
  if (!is_group_replication_plugin_loaded()) {
    return HA_ERR_END_OF_FILE;
  }

  set_position(pos);
  assert(m_pos.m_index < get_row_count());
  return make_row(m_pos.m_index);
}

int table_replication_group_mgr_stats::make_row(uint index) {
  DBUG_TRACE;
  // Set default values.
  m_row.member_host_length = 0;
  m_row.member_port = 0;
  m_row.stat_less_than_10 = 0;
  m_row.stat_between_10_and_20 = 0;
  m_row.stat_between_20_and_30 = 0;
  m_row.stat_between_30_and_40 = 0;
  m_row.stat_between_40_and_50 = 0;
  m_row.stat_between_50_and_60 = 0;
  m_row.stat_between_60_and_70 = 0;
  m_row.stat_between_70_and_80 = 0;
  m_row.stat_between_80_and_90 = 0;
  m_row.stat_between_90_and_100 = 0;
  m_row.stat_between_100_and_200 = 0;
  m_row.stat_between_200_and_300 = 0;
  m_row.stat_between_300_and_400 = 0;
  m_row.stat_between_400_and_500 = 0;
  m_row.stat_between_500_and_1000 = 0;
  m_row.stat_more_than_1000 = 0;

  // Set callbacks on GROUP_REPLICATION_GROUP_MEMBERS_CALLBACKS.
  const GROUP_REPLICATION_MGR_STATS_CALLBACKS callbacks = {
      &m_row,
      &set_member_host,
      &set_member_port,
      &set_stat_less_than_10,
      &set_stat_between_10_and_20,
      &set_stat_between_20_and_30,
      &set_stat_between_30_and_40,
      &set_stat_between_40_and_50,
      &set_stat_between_50_and_60,
      &set_stat_between_60_and_70,
      &set_stat_between_70_and_80,
      &set_stat_between_80_and_90,
      &set_stat_between_90_and_100,
      &set_stat_between_100_and_200,
      &set_stat_between_200_and_300,
      &set_stat_between_300_and_400,
      &set_stat_between_400_and_500,
      &set_stat_between_500_and_1000,
      &set_stat_larger_than_1000,
  };

  // Query plugin and let callbacks do their job.
  if (get_group_replication_mgr_stats_info(index, callbacks)) {
    DBUG_PRINT("info", ("Group Replication stats not available!"));
  } else {
  }

  return 0;
}

int table_replication_group_mgr_stats::read_row_values(TABLE *table,
                                                       unsigned char *buf,
                                                       Field **fields,
                                                       bool read_all) {
  Field *f;

  assert(table->s->null_bytes == 1);
  buf[0] = 0;

  for (; (f = *fields); fields++) {
    if (read_all || bitmap_is_set(table->read_set, f->field_index())) {
      switch (f->field_index()) {
        case 0: /** member_host */
          set_field_char_utf8(f, m_row.member_host, m_row.member_host_length);
          break;
        case 1: /** member_port */
          if (m_row.member_port > 0) {
            set_field_ulong(f, m_row.member_port);
          } else {
            f->set_null();
          }
          break;
        case 2:
          set_field_ulonglong(f, m_row.stat_less_than_10);
          break;
        case 3:
          set_field_ulonglong(f, m_row.stat_between_10_and_20);
          break;
        case 4:
          set_field_ulonglong(f, m_row.stat_between_20_and_30);
          break;
        case 5:
          set_field_ulonglong(f, m_row.stat_between_30_and_40);
          break;
        case 6:
          set_field_ulonglong(f, m_row.stat_between_40_and_50);
          break;
        case 7:
          set_field_ulonglong(f, m_row.stat_between_50_and_60);
          break;
        case 8:
          set_field_ulonglong(f, m_row.stat_between_60_and_70);
          break;
        case 9:
          set_field_ulonglong(f, m_row.stat_between_70_and_80);
          break;
        case 10:
          set_field_ulonglong(f, m_row.stat_between_80_and_90);
          break;
        case 11:
          set_field_ulonglong(f, m_row.stat_between_90_and_100);
          break;
        case 12:
          set_field_ulonglong(f, m_row.stat_between_100_and_200);
          break;
        case 13:
          set_field_ulonglong(f, m_row.stat_between_200_and_300);
          break;
        case 14:
          set_field_ulonglong(f, m_row.stat_between_300_and_400);
          break;
        case 15:
          set_field_ulonglong(f, m_row.stat_between_400_and_500);
          break;
        case 16:
          set_field_ulonglong(f, m_row.stat_between_500_and_1000);
          break;
        case 17:
          set_field_ulonglong(f, m_row.stat_more_than_1000);
          break;

        default:
          assert(false);
      }
    }
  }
  return 0;
}
