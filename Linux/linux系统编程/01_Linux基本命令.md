# Linux 基本命令

## 主键盘快捷键：

上        Ctrl-p 
下        Ctrl-n 
左        Ctrl-b 
右        Ctrl-f 
Del        Ctrl-d delete   光标后面的
Home       Ctrl-a      first letter
End        Ctrl-e      end
Backspace     Backspace   delete光标前面的单个字符
**清除整行**     Ctrl-u  
**删除光标到行末**  Ctrl-k
显示上滚     Shift-PgUp
显示下滚     Shift-PgDn
增大终端字体   Ctrl-Shift-+
减小终端字体   Ctrl- -
**新打开一个终端**   Ctrl-Alt-T
清屏       Ctrl-l   直接用clear也行 
全屏       F11

## Linux 系统目录：

​    bin：存放二进制可执行文件
​    boot：存放开机启动程序
​    dev：存放设备文件： 字符设备、块设备
​    home：存放普通用户
​    etc：用户信息和系统配置文件 passwd、group
​    lib：库文件：libc.so.6
​    root：管理员宿主目录（家目录）
​    usr：用户资源管理目录

## Linux 系统文件类型： 7/8 种

​    普通文件：-
​    目录文件：d
​    字符设备文件：c
​    块设备文件：b
​    软连接：l
​    管道文件：p
​    套接字：s
​    未知文件

## 目录和文件操作

### cd – 进入一个目录

- cd ..	返回上一级目录
- cd ~    返回家目录
- cd /     返回主目录
- cd -     切换到上次的目录

### pwd  返回当前目录路径

### ls 列出当前文件夹下目录项

  - ll 竖排显示目录项和详细信息，ls -l的缩写
  - ls -l 显示目录项详细信息
  - ls -l dirname 显示dirname中目录详细信息
  - ls -dl dirname  显示dirname本身的详细信息
  - ls -R 递归查看目录
  - ls -Rl 递归展示详细信息
  - ls -a 显示隐藏文件

### 文件权限说明

- 目录项详细信息

  文件权限  硬链接计数  所有者  所属组 大小  时间  文件名/文件夹名

- 权限具体展开

  -rwxr—r—读写执行权限（4、2、1）

### 文件操作

- mkdir dirname 新建目录

- rmdir dirname 删除空目录，非空目录删不掉

- touch filename  创建名为 filename 的空文件

- rm filename删除文件

- rm -r dirname 递归删除目录

- rm -rf dirname 强制删除

- mv file1 file2 location   将文件1和文件2移动到目标位置

### cp 复制命令

- cp filename dirname 复制文件到目录

- cp filename1 filename2 复制文件1并重命名为文件2

- cp -a dirname1 dirname2 复制目录1及其下所有文件到目录2

- cp -r dirname1 dirname2 递归复制目录1到目录2

  这里-a和-r的差别在于，-a是完全复制，文件权限，改动时间什么的也完全相同。

### 查看文件

- cat filename 查看文件内容
  - cat 读取终端，就是回显

- tac filename 逆转查看文件内容

- more filename 
  - 和cat差不多，但是对于大文件查看很强势
  - 空格翻页，回车一行
  - 用q或者Ctrl-c退出

- less filename 
  - 也和cat差不多
  - 空格翻页，回车一行
  - 用q或者Ctrl-c退出

- head -n filename 查看文件前n行
  - 不加-n参数默认查看10行

- tail -n filename 查看文件后n行
  - 默认查看10行，顺序显示的，不是倒序显示，1-10查看后4行是78910

- tree 命令，查看当前目录结构树

## 软链接和硬链接

- **ln -s file file.s 创建一个软链接**

软链接就像windows下的快捷方式，创建软链接最好使用源文件的绝对路径

- **ln file file.h 创建一个硬链接**
  - 创建硬链接后，文件的硬链接计数 +1，无论更改哪个硬链接或者文件本身，这两个文件的变化同步
  - 源文件和硬链接的 Inode 是相同的，每个文件都有唯一的 Inode，直观理解起来就像 C++ 里面的引用，对于同一个文件，无论有多少引用，在访问时，都是这个文件，所以修改就是同步的。
  - 当删除一个硬链接时，文件的硬链接计数 -1，当这个计数减为 0 时，才会删除这个文件

## 创建修改用户和用户组

- whoami 查看当前用户

- **chmod 修改权限操作**

  - chmod 操作码 filename 直接用操作码修改文件权限

    **chmod 764 filename** 

- **sudo adduser newusername 添加新用户**

- chown username filename 修改文件所有者

- su username 切换当前用户为username

- **sudo addgroup groupname 添加新的用户组**

- sudo chgrp groupname filename 修改文件所属用户组

- sudo chown username:groupname filename 同时修改文件所属用户和用户组

- **sudo deluser username 删除用户**

- **sudo delgroup groupname 删除用户组**

## find 命令：找文件

- -type 按**文件类型**搜索 d/p/s/c/b/l/ f:文件
- -name 按**文件名**搜索       
  - find ./ -name "*file*.jpg"

- -maxdepth **指定搜索深度**。应作为第一个参数出现。
  - find ./ -maxdepth 1 -name "*file*.jpg"

- -size 按**文件大小**搜索. 单位：k、M、G
  - find /home/itcast -size +20M -size -50M

- -atime、mtime、ctime 天 amin、mmin、cmin 分钟。

- -exec：将find搜索的结果集**执行某一指定命令**。
  - find /usr/ -name '*tmp*' -exec ls -ld {} \;

- -ok: 以交互式的方式 将find搜索的结果集执行某一指定命令

- -xargs：将find搜索的结果集执行某一指定命令。当结果集数量过大时，可以分片映射。
  - find /usr/ -name '*tmp*' | xargs ls -ld 

- -print0：（将结果集打印输出，在每行末尾加null）
  - find /usr/ -name '*tmp*' -print0 | xargs -print0 ls -ld

（防止文件名带有空格，xargs查找出错；xargs默认以空格为分隔依据，标明以 null 作为分隔依据）

## grep命令：找文件内容

- grep -r 'copy' ./ -n
  - -r参数：递归，进入目录
  - -n参数：显示行号

- **ps aux | grep 'cupsd' -- 检索进程结果集**

## 软件安装：

1. 更新软件资源列表到本地 **sudo apt-get update**
2. 安装 **sudo apt-get install 软件名**
3. 卸载 **sudo apt-get remove 软件名**
4. 使用软件包（.deb）安装：  **sudo dpkg -i 安装包名**

## 解压与压缩

### tar压缩：

**tar -zcvf   要生成的压缩包名  压缩材料**

- tar zcvf  test.tar.gz  file1 dir2   使用 gzip 方式压缩
- tar jcvf  test.tar.gz  file1 dir2   使用 bzip2 方式压缩。

### tar解压：

**将 压缩命令中的 c --> x**

- tar zxvf  test.tar.gz   使用 gzip 方式解压缩
- tar jxvf  test.tar.gz   使用 bzip2方式解压缩。
