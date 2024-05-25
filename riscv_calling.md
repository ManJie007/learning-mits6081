the C compiler standards for RV32 and RV64 programs and two calling conventions: 
    1.the convention for the base ISA plus standard general extensions (RV32G/RV64G),
    2.and the soft-float convention for implementations lacking floating-point units (e.g., RV32I/RV64I).

In both RV32 and RV64 C compilers, the C type #int is 32 bits wide.
#longs and #pointers, on the other hand, are both as wide as a integer register, so in RV32, both are 32 bits wide, while in RV64, both are 64 bits wide.

Equivalently, RV32 employs an ILP32 integer model, while RV64 is LP64.
    RV32（32位 RISC-V）采用的是 ILP32 整数模型:
        整型 (int)、长整型 (long) 和指针 (void\*) 都是 32 位。
    RV64（64位 RISC-V）采用的是 LP64 整数模型:
        整型 (int) 仍然是 32 位,
        长整型 (long) 和指针 (void\*) 都是 64 位。

In both RV32 and RV64, the C type #long #long is a 64-bit integer, #float is a 32-bit IEEE 754-2008 floating-point number, #double is a 64-bit IEEE 754-2008 floating-point number, and #long #double is a 128-bit IEEE floating-point number.

The C types #char and #unsigned char are 8-bit unsigned integers and are #zero-extended when stored in a RISC-V integer register.

#unsigned #short is a 16-bit unsigned integer and is #zeroextended when stored in a RISC-V integer register.

#signed char is an 8-bit signed integer and is #sign-extended when stored in a RISC-V integer register, i.e. bits (XLEN-1)..7 are all equal. 

#short is a 16-bit signed integer and is #sign-extended when stored in a register.

The RV32 and RV64 C compiler and compliant software keep all of the above datatypes naturally aligned when stored in memory.

C type          |     Description                  |     Bytes in RV32     |     Bytes in RV64
char            |     Character value/byte         |     1                 |     1
short           |     Short integer                |     2                 |     2 
int             |     Integer                      |     4                 |     4
long            |     Long integer                 |     4                 |     8
long long       |     Long long integer            |     8                 |     8
void*           |     Pointer                      |     4                 |     8
float           |     Single-precision float       |     4                 |     4
double          |     Double-precision float       |     8                 |     8
long double     |     Extended-precision float     |     16                |     16

RVG Calling Convention

The RISC-V calling convention passes arguments in registers when possible. 
Up to eight integer registers, #a0–a7, and up to eight floating-point registers, #fa0–fa7, are used for this purpose.

If the arguments to a function are conceptualized as fields of a C #struct, each with pointer alignment, the argument registers are a shadow of the first eight pointer-words of that #struct.
     If argument i < 8 is a floating-point type, it is passed in floating-point register #fai; 
     otherwise, it is passed in integer register #ai. 
However, floating-point arguments that are part of #unions or #array fields of structures are passed in integer registers. 
Additionally, floating-point arguments to variadic functions (except those that are explicitly named in the parameter list) are passed in integer registers.

Arguments smaller than a pointer-word are passed in the least-significant bits of argument registers.
    Correspondingly, sub-pointer-word arguments passed on the #stack appear in the lower addresses of a pointer-word, since RISC-V has a #little-endian memory system.

When primitive arguments twice the size of a pointer-word are passed on the #stack, they are naturally #aligned. 
    When they are passed in the integer registers, they reside in an #aligned #even-odd register pair, with the even register holding the least-significant bits. In RV32, for example, the function void foo(int, long long) is passed its first argument in a0 and its second in a2 and a3. Nothing is passed in a1.

Arguments more than twice the size of a pointer-word are #passed by #reference.

The portion of the conceptual struct that is not passed in argument registers is #passed on the #stack. The stack pointer #sp points to the first argument not passed in a register.

#Values are returned from functions in integer registers a0 and a1 and floating-point registers fa0 and fa1. 
    Floating-point values are returned in floating-point registers only if they are primitives or members of a struct consisting of only one or two floating-point values. 
    Other return values that fit into two pointer-words are returned in a0 and a1. 
    Larger return values are passed entirely in #memory; the caller allocates this memory region and passes a pointer to it as an implicit first parameter to the callee.

In the standard RISC-V calling convention, the stack grows #downward and the stack pointer is always kept 16-byte #aligned.

In addition to the argument and return value registers, seven integer registers #t0–t6 and twelve floating-point registers #ft0–ft11 are temporary registers that are volatile across calls and must be saved by the caller if later used. 
Twelve integer registers #s0–s11 and twelve floating-point registers #fs0–fs11 are preserved across calls and must be saved by the callee if used. 

Register   |    ABI Name      |         Description                       |     Saver
x0         |    zero          |         Hard-wired zero                   |     
x1         |    ra            |         Return address                    |     Caller
x2         |    sp            |         Stack pointer                     |     Callee
x3         |    gp            |         Global pointer                    |     
x4         |    tp            |         Thread pointer                    |     
x5-7       |    t0-2          |         Temporaries                       |     Caller
x8         |    s0/fp         |         Saved register/frame pointer      |     Callee
x9         |    s1            |         Saved register                    |     Callee
x10-11     |    a0-1          |         Function arguments/return values  |     Caller
x12-17     |    a2-7          |         Function arguments                |     Caller
x18-27     |    s2-11         |         Saved registers                   |     Callee
x28-31     |    t3-6          |         Temporaries                       |     Caller
f0-7       |    ft0-7         |         FP temporaries                    |     Caller
f8-9       |    fs0-1         |         FP saved registers                |     Callee
f10-11     |    fa0-1         |         FP arguments/return values        |     Caller
f12-17     |    fa2-7         |         FP arguments                      |     Caller
f18-27     |    fs2-11        |         FP saved registers                |     Callee
f28-31     |    ft8-11        |         FP temporaries                    |     Caller

The soft-float calling convention is used on RV32 and RV64 implementations that lack floatingpoint hardware. It avoids all use of instructions in the F, D, and Q standard extensions, and hence the f registers.

Integral arguments are passed and returned in the same manner as the #RVG convention, and the stack discipline is the same. Floating-point arguments are passed and returned in integer registers, using the rules for integer arguments of the same size. In RV32, for example, the function double foo(int, double, long double) is passed its first argument in a0, its second argument in a2 and a3, and its third argument by reference via a4; its result is returned in a0 and a1. In RV64, the arguments are passed in a0, a1, and the a2-a3 pair, and the result is returned in a0.

The dynamic rounding mode and accrued exception flags are accessed through the routines provided by the C99 header fenv.h.

处理器并不能理解C语言。处理器能够理解的是汇编语言，或者更具体的说，处理器能够理解的是二进制编码之后的汇编代码。
任何一个处理器都有一个关联的ISA（Instruction Sets Architecture），ISA就是处理器能够理解的指令集。每一条指令都有一个对应的二进制编码或者一个Opcode。当处理器在运行时，如果看见了这些编码，那么处理器就知道该做什么样的操作。
所以通常来说，要让C语言能够运行在你的处理器之上。我们首先要写出C程序，之后这个C程序需要被编译成汇编语言。这个过程中有一些链接和其他的步骤。之后汇编语言会被翻译成二进制文件也就是.obj或者.o文件。
汇编语言中没有很好的控制流程，没有循环（注，但是有基于#lable的跳转），虽然有函数但是与你们知道的C语言函数不太一样，汇编语言中的函数是以label的形式存在而不是真正的函数定义。汇编语言是一门非常底层的语言，许多其他语言，比如C++，都会编译成汇编语言。运行任何编译型语言之前都需要先生成汇编语言。

RISC-V和x86并没有它们第一眼看起来那么相似。RISC-V中的RISC是精简指令集（Reduced Instruction Set Computer）的意思，而x86通常被称为CISC，复杂指令集（Complex Instruction Set Computer）。这两者之间有一些关键的区别：
    1.首先是指令的数量。实际上，创造RISC-V的一个非常大的初衷就是因为Intel手册中指令数量太多了。x86-64指令介绍由3个文档组成，并且新的指令以每个月3条的速度在增加。因为x86-64是在1970年代发布的，所以我认为现在有多于15000条指令。RISC-V指令介绍由两个文档组成。在这节课中，不需要你们记住每一个RISC-V指令，但是如果你感兴趣或者你发现你不能理解某个具体的指令的话，在课程网站的参考页面有RISC-V指令的两个文档链接。这两个文档包含了RISC-V的指令集的所有信息，分别是240页和135页，相比x86的指令集文档要小得多的多。这是有关RISC-V比较好的一个方面。所以在RISC-V中，我们有更少的指令数量。
    2.除此之外，RISC-V指令也更加简单。在x86-64中，很多指令都做了不止一件事情。这些指令中的每一条都执行了一系列复杂的操作并返回结果。但是RISC-V不会这样做，RISC-V的指令趋向于完成更简单的工作，相应的也消耗更少的CPU执行时间。这其实是设计人员的在底层设计时的取舍。并没有一些非常确定的原因说RISC比CISC更好。它们各自有各自的使用场景。
    3.相比x86来说，RISC另一件有意思的事情是它是开源的。这是市场上唯一的一款开源指令集，这意味着任何人都可以为RISC-V开发主板。RISC-V是来自于UC-Berkly的一个研究项目，之后被大量的公司选中并做了支持，网上有这些公司的名单，许多大公司对于支持一个开源指令集都感兴趣。

如果查看RISC-V的文档，可以发现RISC-V的特殊之处在于：它区分了Base Integer Instruction Set和Standard Extension Instruction Set。Base Integer Instruction Set包含了所有的常用指令，比如add，mult。除此之外，处理器还可以选择性的支持Standard Extension Instruction Set。例如，一个处理器可以选择支持Standard Extension for Single-Precision Float-Point。这种模式使得RISC-V更容易支持向后兼容。 每一个RISC-V处理器可以声明支持了哪些扩展指令集，然后编译器可以根据支持的指令集来编译代码。

```
.section .text
.global sum_to
/*
 int sum _to (int n) { 
    int acc = 0;
    for (int i = 0; i <= n; i++) { 
        acc += i;
    }
    return acc;
 }
*/
sum_to:
    mv to, ao           # t0 <- a0
    li a0, 0            # a0 <- 0
Loop:
    add ao, ao, tO      # a0 <- a0 + t0 
    addi to, to, -1     # t0 <- t0 - 1
    bnez to, loop       # if t0 != 0: pc <- loop
    ret
```
如果你在你自己的计算机编写同样的C代码并编译，你得到的极有可能是差别较大的汇编代码。这里有很多原因，有一些原因我们之后会讲，有一些原因是因为编译器。当将C代码编译成汇编代码时，现代的编译器会执行各种各样的优化，所以你们自己编译得到的汇编代码可能看起来是不一样的。例如，当你在gdb中做debug的时候，有时候你会看到gdb提示你说某些变量被优化掉了，这意味着编译器决定了自己不再需要那个变量，变量以及相关的信息会在某个时间点删掉。


                                MAXVA --> --------------
                                          | trampoline |
                                          | trapframe  |          -----   --------------                                                   
                                          |            |            ^     | argument 0 |
                                          |            |            |     |   ...      |
                                          | heap       |            |     | argument N |
                                          |            |            |     |    0       | nul-terminated string
                                          |            |                  | address of | argument N argv[argc]
                                          |            |          stack   |   ...      |                      
                                          |            |                  | address of | argument 0 argv[0]   
                                PAGESIZE  | stack      |            |     | address of | address of argv[0]  argv argument of main
                                          | guard page |            |     | argc       | address argument of main      
                                          | data       |            |     | 0xFFFFFFF  | return PC of main             
                                          | text       |            v     | (empty)    |                               
                                       0  --------------          -----   --------------


每个进程的page table中有一个区域是text，汇编代码中的text表明这部分是代码，并且位于page table的text区域中。text中保存的就是代码。

如果你对内核比较感兴趣，在编译完之后，你可以查看kernel.asm文件，你可以看到XV6完整内核的汇编版本。文件中每一行左边的数字表明的是这条指令会在内存中的哪个位置，这个信息非常有用。在汇编代码中还可以看到函数对应的label，以及它们是在哪里定义的。这些信息在我们调试代码的时候可能会非常非常有用。

学生提问：.asm文件和.s文件有什么区别？
TA：我并不是百分百确定。这两类文件都是汇编代码，.asm文件中包含大量额外的标注，而.s文件中没有。所以通常来说当你编译你的C代码，你得到的是.s文件。如果你好奇我们是如何得到.asm文件，makefile里面包含了具体的步骤。

gdb中输入tui enable可以打开源代码展示窗口。
在gdb中输入layout asm，可以在tui窗口看到所有的汇编指令。再输入layout reg可以看到所有的寄存器信息。
如果你关心你设置了哪些断点，或着你跟踪代码的时候迷糊了，你可以在gdb中输入info breakpoints，你可以看到所有设置了的断点。
类似的，你也可以通过输入info reg查看寄存器的信息。
gdb和tmux有上百个快捷指令，可以通过google去查找，对于gdb，也可以使用apropos指令查看帮助。

RISC-V寄存器
寄存器是CPU或者处理器上，预先定义的可以用来存储数据的位置。寄存器之所以重要是因为汇编代码并不是在内存上执行，而是在寄存器上执行，也就是说，当我们在做add，sub时，我们是对寄存器进行操作。 所以你们通常看到的汇编代码中的模式是，我们通过load将数据存放在寄存器中，这里的数据源可以是来自内存，也可以来自另一个寄存器。 之后我们在寄存器上执行一些操作。如果我们对操作的结果关心的话，我们会将操作的结果store在某个地方。这里的目的地可能是内存中的某个地址，也可能是另一个寄存器。 这就是通常使用寄存器的方法。

Register   |    ABI Name      |         Description                       |     Saver
x0         |    zero          |         Hard-wired zero                   |     
x1         |    ra            |         Return address                    |     Caller
x2         |    sp            |         Stack pointer                     |     Callee
x3         |    gp            |         Global pointer                    |     
x4         |    tp            |         Thread pointer                    |     
x5-7       |    t0-2          |         Temporaries                       |     Caller
x8         |    s0/fp         |         Saved register/frame pointer      |     Callee
x9         |    s1            |         Saved register                    |     Callee
x10-11     |    a0-1          |         Function arguments/return values  |     Caller
x12-17     |    a2-7          |         Function arguments                |     Caller
x18-27     |    s2-11         |         Saved registers                   |     Callee
x28-31     |    t3-6          |         Temporaries                       |     Caller
f0-7       |    ft0-7         |         FP temporaries                    |     Caller
f8-9       |    fs0-1         |         FP saved registers                |     Callee
f10-11     |    fa0-1         |         FP arguments/return values        |     Caller
f12-17     |    fa2-7         |         FP arguments                      |     Caller
f18-27     |    fs2-11        |         FP saved registers                |     Callee
f28-31     |    ft8-11        |         FP temporaries                    |     Caller

寄存器是用来进行任何运算和数据读取的最快的方式，这就是为什么使用它们很重要，也是为什么我们更喜欢使用寄存器而不是内存。 当我们调用函数时，你可以看到这里有a0 - a7寄存器。通常我们在谈到寄存器的时候，我们会用它们的ABI名字。不仅是因为这样描述更清晰和标准，同时也因为在写汇编代码的时候使用的也是ABI名字。 第一列中的寄存器名字并不是超级重要，它唯一重要的场景是在RISC-V的Compressed Instruction中。基本上来说，RISC-V中通常的指令是64bit，但是在Compressed Instruction中指令是16bit。在Compressed Instruction中我们使用更少的寄存器，也就是x8 - x15寄存器。我猜你们可能会有疑问，为什么s1寄存器和其他的s寄存器是分开的，因为s1在Compressed Instruction是有效的，而s2-11却不是。除了Compressed Instruction，寄存器都是通过它们的ABI名字来引用。

a0到a7寄存器是用来作为函数的参数。如果一个函数有超过8个参数，我们就需要用内存了。从这里也可以看出，当可以使用寄存器的时候，我们不会使用内存，我们只在不得不使用内存的场景才使用它。

Caller Saved寄存器在函数调用的时候不会保存
Callee Saved寄存器在函数调用的时候会保存

这里的意思是，一个Caller Saved寄存器可能被其他函数重写。假设我们在函数a中调用函数b，任何被函数a使用的并且是Caller Saved寄存器，调用函数b可能重写这些寄存器。我认为一个比较好的例子就是Return address寄存器（注，保存的是函数返回的地址），你可以看到ra寄存器是Caller Saved，这一点很重要，它导致了当函数a调用函数b的时侯，b会重写Return address。所以基本上来说，任何一个Caller Saved寄存器，作为调用方的函数要小心可能的数据可能的变化；任何一个Callee Saved寄存器，作为被调用方的函数要小心寄存器的值不会相应的变化。我经常会弄混这两者的区别，然后会到这张表来回顾它们。

如果你们还记得的话，所有的寄存器都是64bit，各种各样的数据类型都会被改造的可以放进这64bit中。比如说我们有一个32bit的整数，取决于整数是不是有符号的，会通过在前面补32个0或者1来使得这个整数变成64bit并存在这些寄存器中。

Stack
栈之所以很重要的原因是，它使得我们的函数变得有组织，且能够正常返回。
下面是一个非常简单的栈的结构图，其中每一个区域都是一个Stack Frame，每执行一次函数调用就会产生一个Stack Frame。

   |--> Return address           |      
   |    To Prev. Frame(fp)       |      
   |    Saved Registers          | stack frame (Generated by fn calls)     
   |    Local Variables          |      
   |        ...                  |      
   |
   |
   |    Return address     <--|         
   ---- To Prev. Frame(fp)    |         
        Saved Registers       |                                            
        Local Variables       |         
            ...               |         
                              |

   fp   Return address        |         
        To Prev. Frame(fp) ----         
        Saved Registers                                                    
        Local Variables                 
   sp       ...                         

每一次我们调用一个函数，函数都会为自己创建一个Stack Frame，并且只给自己用。函数通过移动Stack Pointer来完成Stack Frame的空间分配。

对于Stack来说，是从高地址开始向低地址使用。所以栈总是向下增长。当我们想要创建一个新的Stack Frame的时候，总是对当前的Stack Pointer做减法。一个函数的Stack Frame包含了保存的寄存器，本地变量，并且，如果函数的参数多于8个，额外的参数会出现在Stack中。所以Stack Frame大小并不总是一样，即使在这个图里面看起来是一样大的。不同的函数有不同数量的本地变量，不同的寄存器，所以Stack Frame的大小是不一样的。但是有关Stack Frame有两件事情是确定的：
    Return address总是会出现在Stack Frame的第一位
    指向前一个Stack Frame的指针也会出现在栈中的固定位置

有关Stack Frame中有两个重要的寄存器:
第一个是SP（Stack Pointer），它指向Stack的底部并代表了当前Stack Frame的位置。
第二个是FP（Frame Pointer），它指向当前Stack Frame的顶部。因为Return address和指向前一个Stack Frame的的指针都在当前Stack Frame的固定位置，所以可以通过当前的FP寄存器寻址到这两个数据。

我们保存前一个Stack Frame的指针的原因是为了让我们能跳转回去。所以当前函数返回时，我们可以将前一个Frame Pointer存储到FP寄存器中。所以我们使用Frame Pointer来操纵我们的Stack Frames，并确保我们总是指向正确的函数。

Stack Frame必须要被汇编代码创建，所以是编译器生成了汇编代码，进而创建了Stack Frame。所以通常，在汇编代码中，函数的最开始你们可以看到Function prologue，之后是函数的本体，最后是Epilogue。这就是一个汇编函数通常的样子。

                Function prologue
Asm Function    Body
                Epllogue

在我们之前的sum\_to函数中，只有函数主体，并没有Stack Frame的内容。它这里能正常工作的原因是它足够简单，并且它是一个leaf函数。leaf函数是指不调用别的函数的函数，它的特别之处在于它不用担心保存自己的Return address或者任何其他的Caller Saved寄存器，因为它不会调用别的函数。

而另一个函数sum\_then\_double就不是一个leaf函数了，这里你可以看到它调用了sum\_to。

```
.global sum_then_double 
sum_then_double:
    addi sp, sp, -16;      |    prologue    
    sd ra, 0(sp)           |    这里我们对Stack Pointer减16，这样我们为新的Stack Frame创建了16字节的空间。之后我们将Return address保存在Stack Pointer位置。
    call sum_to
    li to, 2
    mul ao, ao, to 
    ld ra, 0(sp)           |    Epilogue
    addi sp, sp, 16        |    这里首先将Return address加载回ra寄存器，通过对Stack Pointer加16来删除刚刚创建的Stack Frame，最后ret从函数中退出。
    ret
```

如果我们在gdb中输入info frame，可以看到有关当前Stack Frame许多有用的信息。
如果输入backtrace（简写bt）可以看到从当前调用栈开始的所有Stack Frame。
如果对某一个Stack Frame感兴趣，可以先定位到那个frame再输入info frame。

学生提问：为什么有的时候编译器会优化掉argc或者argv？这个以前发生过。
TA：这意味着编译器发现了一种更有效的方法，不使用这些变量，而是通过寄存器来完成所有的操作。如果一个变量不是百分百必要的话，这种优化还是很有常见的。我们并没有给你编译器的控制能力，但是在你们的日常使用中，你可以尝试设置编译器的optimization flag为0，不过就算这样，编译器也会做某些程度的优化。

在 GDB 中可以通过以下方式设置变量的值或控制跳过指令:
设置变量的值:
使用 set variable <变量名> = <值> 命令可以直接修改变量的值。
例如: set variable count = 10

跳过指令:
使用 skip 命令可以跳过指定的指令。
skip [行号] 可以跳过指定的行号。
skip if <条件表达式> 可以在满足条件时跳过指令。

执行汇编指令:
使用 stepi 或 nexti 命令可以单步执行汇编指令。
set {type}addr = value 可以直接修改内存地址的值。

断点相关:
break [行号|函数名] 可以在指定行号或函数处设置断点。
condition <断点编号> <条件表达式> 可以为断点添加条件。
disable <断点编号> 可以禁用指定的断点。

观察点:
watch <表达式> 可以在表达式发生变化时停止程序执行。
rwatch <表达式> 可以在表达式被读取时停止程序执行。
awatch <表达式> 可以在表达式被读取或写入时停止程序执行。

进程控制:
continue 可以继续执行程序直到遇到下一个断点。
finish 可以执行完当前函数并返回到调用函数。
until [行号] 可以执行程序直到指定行号。

Struct
基本上来说，struct在内存中是一段连续的地址，如果我们有一个struct，并且有f1，f2，f3三个字段。

**
当我们创建这样一个struct时，内存中相应的字段会彼此相邻。你可以认为struct像是一个数组，但是里面的不同字段的类型可以不一样。（注，这应该是这一节中最有用的一句话了。。。）
**
