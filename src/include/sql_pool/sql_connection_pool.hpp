#ifndef SQL_CONNECTION_POOL_
#define SQL_CONNECTION_POOL_

#include <mysql/client_plugin.h>
#include <mysql/mysql.h>
#include <string>
#include <vector>

/*
  mysql数据库连接池
*/
class SqlConnectionPool {
public:
  SqlConnectionPool(std::string url, int port, std::string user,
                    std::string password, std::string database, int max_conn)
      : url_(url), port_(port), user_(user), password_(password),
        database_(database), max_conn_(max_conn), conn_num_(0), free_conn_(0) {
          Init();
        }
  SqlConnectionPool(const SqlConnectionPool&) = delete;
  SqlConnectionPool &operator=(const SqlConnectionPool&) = delete;
  virtual ~SqlConnectionPool() {
    Destory();
  }
  // 销毁连接池
  void Destory();

  // 获取连接
  MYSQL *GetConnection();

  // 释放连接
  bool ReleaseConnection(MYSQL *conn);
private:
  // 初始化连接池
  void Init();

private:
  // 最大连接数 
  int max_conn_;
  // 当前已使用连接数
  int conn_num_;
  // 空闲连接数
  int free_conn_;

  // 主机地址
  std::string url_;
  int port_;
  std::string user_;
  std::string password_;
  std::string database_;

  // 连接池
  std::vector<MYSQL*> idl_pool;
};

#endif