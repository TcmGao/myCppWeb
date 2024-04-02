#include "sql_pool/sql_connection_pool.hpp"
#include <mysql/mysql.h>

void SqlConnectionPool::Init() {
  for (int i = 0; i < max_conn_; i++) {
    MYSQL *conn = nullptr;
    conn = mysql_init(conn);

    if (nullptr == conn) {
      // 日志打印
      exit(1);
    }
    conn = mysql_real_connect(conn, url_.c_str(), user_.c_str(), password_.c_str(), database_.c_str(), port_, nullptr, 0);
    if (nullptr == conn) {
      // 日志打印
      exit(1);
    }
    idl_pool.push_back(conn);
    ++free_conn_;
  }
  max_conn_ = free_conn_;
}

MYSQL *SqlConnectionPool::GetConnection() {
  MYSQL *conn = nullptr;
  // 加锁，看一下bs怎么用的sf的锁，以及单例模式。学习一下设计理念
  return conn;
}