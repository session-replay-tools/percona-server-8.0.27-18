/*
   Copyright (c) 2013, 2021, Oracle and/or its affiliates.

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

#ifndef TABLE_REPLICATION_GROUP_MGR_STATS_H
#define TABLE_REPLICATION_GROUP_MGR_STATS_H

/**
  @file storage/perfschema/table_replication_group_mgr_stats.h
  Table replication_group_mgr_stats (declarations).
*/

#include <sys/types.h>

#include "my_base.h"
#include "my_hostname.h"  // HOSTNAME_LENGTH
#include "mysql_com.h"
#include "sql/rpl_info.h"
#include "sql/sql_const.h"  // UUID_LENGTH
#include "storage/perfschema/pfs_engine_table.h"

class Field;
class Plugin_table;
struct TABLE;
struct THR_LOCK;

/**
  @addtogroup performance_schema_tables
  @{
*/

/**
  A row in connection nodes table. The fields with string values have an
  additional
  length field denoted by @<field_name@>_length.
*/
struct st_row_group_mgr_stat {
  char member_host[HOSTNAME_LENGTH];
  uint member_host_length;
  uint member_port;
  unsigned long long int stat_less_than_10;
  unsigned long long int stat_between_10_and_20;
  unsigned long long int stat_between_20_and_30;
  unsigned long long int stat_between_30_and_40;
  unsigned long long int stat_between_40_and_50;
  unsigned long long int stat_between_50_and_60;
  unsigned long long int stat_between_60_and_70;
  unsigned long long int stat_between_70_and_80;
  unsigned long long int stat_between_80_and_90;
  unsigned long long int stat_between_90_and_100;
  unsigned long long int stat_between_100_and_200;
  unsigned long long int stat_between_200_and_300;
  unsigned long long int stat_between_300_and_400;
  unsigned long long int stat_between_400_and_500;
  unsigned long long int stat_between_500_and_1000;
  unsigned long long int stat_more_than_1000;
};

/** Table PERFORMANCE_SCHEMA.replication_group_mgr_stats. */
class table_replication_group_mgr_stats : public PFS_engine_table {
  typedef PFS_simple_index pos_t;

 private:
  int make_row(uint index);

  /** Table share lock. */
  static THR_LOCK m_table_lock;
  /** Table definition. */
  static Plugin_table m_table_def;

  /** Current row */
  st_row_group_mgr_stat m_row;
  /** Current position. */
  pos_t m_pos;
  /** Next position. */
  pos_t m_next_pos;

 protected:
  /**
    Read the current row values.
    @param table            Table handle
    @param buf              row buffer
    @param fields           Table fields
    @param read_all         true if all columns are read.
  */

  int read_row_values(TABLE *table, unsigned char *buf, Field **fields,
                      bool read_all) override;

  table_replication_group_mgr_stats();

 public:
  ~table_replication_group_mgr_stats() override;

  /** Table share. */
  static PFS_engine_table_share m_share;
  static PFS_engine_table *create(PFS_engine_table_share *);
  static ha_rows get_row_count();
  int rnd_next() override;
  int rnd_pos(const void *pos) override;
  void reset_position(void) override;
};

/** @} */
#endif
