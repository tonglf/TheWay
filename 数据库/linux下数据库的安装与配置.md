# linux下数据库的安装与配置

## MySQL

### 安装

```shell
sudo apt-get update
sudo apt-get install mysql-server
```

### 配置文件

配置文件的目录：`/etc/mysql/`

可以打开文件：`sudo vim /etc/mysql/debian.cnf` 查看 MySQL 初始化的用户名和密码

### 登录

可以直接使用 root 用户登录

```shell
sudo mysql -uroot -p
sudo mysql
```

## Redis

