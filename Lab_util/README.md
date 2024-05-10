diff --git a/user/sh.c b/user/sh.c
index 83dd513..066e6c4 100644
--- a/user/sh.c
+++ b/user/sh.c
@@ -53,6 +53,8 @@ int fork1(void);  // Fork but panics on failure.
 void panic(char*);
 struct cmd *parsecmd(char*);
 
+void runcmd(struct cmd *cmd) __attribute__((noreturn));
+
 // Execute cmd.  Never returns.
 void
 runcmd(struct cmd *cmd)


diff --git a/Makefile b/Makefile
index ca9b746..a85136d 100644
--- a/Makefile
+++ b/Makefile
@@ -91,7 +91,7 @@ LD = $(TOOLPREFIX)ld
 OBJCOPY = $(TOOLPREFIX)objcopy
 OBJDUMP = $(TOOLPREFIX)objdump
 
-CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb
+CFLAGS = -Wall -Werror -O -fno-omit-frame-pointer -ggdb -Wno-infinite-recursion
 
 ifdef LAB
 LABUPPER = $(shell echo $(LAB) | tr a-z A-Z)
@@ -195,6 +195,7 @@ UPROGS=\
 	$U/_zombie\
 	$U/_sleep\
 	$U/_pingpong\
+	$U/_primes\
 
 
 
