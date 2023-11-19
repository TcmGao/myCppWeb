# 链接器
1. 链接  
  * 创建静态链接库  
    ```
    # 1. 创建
    gcc -c addvec.c multvec.c
    # rcs中，r是替换库中旧目标文件；c是创无论静态库是否存在，都创建新静态库，s是为目标文件建立索引，加快链接过程
    ar rcs libvector.a addvec.o multvec.o
    # 2. 使用
    gcc -o prog main.o ./libvector.a 
    # 或者使用-L指定查找目录
    gcc -o prog main.o -L. -lvector
    ```
  * 创建动态链接库
    ```
    # 1.创建
    gcc -shared -fpic -o libvector.so addvec.c multvec.c
    # 2.使用
    gcc -o prog main.c -L. -lvector
    # 或者
    gcc -o prog main.c ./libvector.so

    # fpic即position-independent code，位置无关代码，使得动态库可加载到内存任意位置而无需链接器做修改
    ```
  * 生成pic的技术

  