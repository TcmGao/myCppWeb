## 基础知识学习
##### 1. 链接  
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
  * PIC(Position-Independent Code)
    * GOT(Global Offset Table)
      GOT即全局偏移量表，利用数据段和代码段相对位置是一个运行时常量的性质。为每一个动态库中的符号(变量或者函数)建立一个8 Bytes的entry，把符号地址填入每一个entry，这样运行时通过一次间接引用，就可以知道符号的运行时地址。
      GOT在动态库内部会使用，因为数据段和代码段相对位置是确定的，这样在制作so时就能生成位置无关代码，动态库内部的重定位条目就可以被确定下来而不是在链接时才能确定，这样的代价自然就是多了一次间接引用，效率受到影响。
    * PLT(Procedure Linkage Table)
      光是GOT还不够，目标模块在调用动态库时，还不知道要调用的函数在哪，此时为了实现PIC，就需要在运行时借助PLT确定GOT条目。(也可以在加载共享库时解析重定位条目，但这不是PIC，因为需要链接器修改调用模块的代码段，这其实就和静态库没有区别了，需要在链接时就加载所有的库函数，确定重定位条目)。
      真正的动态库就是使用延迟绑定，利用PLT的辅助，在运行时加载需要的函数。一个PLT条目时16 Bytes，原理如下：
      1. 调用模块会跳转到自己的PLT中对应的条目。这个条目包含了一段代码，例如：jump GOT[4]，即跳转到GOT条目对应的地址中。
      2. GOT条目初始时包含的是PLT下一条指令的地址，所以只是简单把控制传送回PLT的下一条指令。
      3. 第二条PLT指令会把GOT条目的id，也就是在GOT中的条目偏移压入栈，例如: pushq $0x1，第[4条]GOT条目的偏移就是[1]，因为前3条GOT条目是特殊值。
      4. 下一条指令跳转到PLT第[0]个条目，先把动态库id压入栈，再jump 到动态链接器。
      5. 动态链接器通过压入的GOT条目偏移，通过一个编译过程中生成的映射关系，找到要调用的实际函数id，这个id再去对应动态库中的函数，找到这个函数地址后，调用函数，把函数地址写入GOT条目。
      6. 下一次再调用函数时，只需要一次间接跳转就可以了

  