# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -g

# 定义源文件和目标文件
SRCS = main.c defs.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

# 主目标
all: program

# 链接目标文件生成可执行文件
program: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.d
	$(CC) $(CFLAGS) -c $< -o $@

# .d改变或者新增时，会重新执行make
-include $(DEPS)

# 生成依赖文件的模式规则
# @command代表不会输出命令,比如@echo "hello"，只会输出hello，如果没有@，就会输出echo "hello";"hello"
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$;

# 清理目标
clean:
	rm -f $(OBJS) $(DEPS) program
.PHONY: clean

# 注意:= 和=区别，前者是马上赋值的，后者是根据最终变量的值赋值的