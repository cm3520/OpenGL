# cpp11

[TOC]

## Features

### _Pragma

### 委派构造函数


### 异常处理 ???


### STL中的函数对象或称仿函数 (非cpp11特性)
仿函数就是重定义了成员函数`operator()`的一种自定义类型对象。其特点是其使用在代码层面与函数的使用并无二样，但其本质却非函数。

仿函数与函数的不同：
* 仿函数可以拥有初始状态。可以通过类的私有成员，并在声明对象的时候对其进行初始化。私有成员的状态就成了仿函数的初始状态。由于声明一个仿函数对象可以拥有多个不同初始状态的实例，因此可以借助仿函数产生多个功能类似却不同的仿函数实例。


### lambda
1. 简介：lambda用来表示一种匿名函数。“函数式编程”是以其概念为基础。
~~~cpp
//lambda函数的一般形式：
[capture](parameters) mutable ->return-type{statement}
~~~
* `[capture]`: 捕捉列表。lambda总是以捕捉列表开始，[]是lambda的引出符。编译器可以根据该引出符判断接下来的代码是否是lambda函数。捕捉列表能够捕捉上下文中的变量以供lambda函数使用。
* `(parameters)`: 参数列表。与普通函数参数列表一致，如果不需要传递参数，则可以连同括号()一起省略。
* `mutable`: mutable修饰符。默认情况下lambda是一个const函数，mutable则可以取消其常量性。当使用mutable时，参数列表不可省略。
* `->return-type`: 返回类型。当不需要返回值时，可以连同->一起省略。此外当返回类型明确的情况下，也可以省略该部分，让编译器自行推导。
* `{statement}`: 函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。

注意：捕获列表不允许变量重复传递，即`[=,var]`是错的；而且传递只有两种：要么是值传递`[=]`，要么是引用传递`[&]`。此外lambda函数仅能捕捉其父作用域中的自动变量，捕捉任何非此作用域或是非自动变量（如静态变量等）都会导致编译器报错。


lambda与仿函数：
功能与内涵非常相似，只是lambda通过捕获参数的方式实现了仿函数通过实列化一个对象的方式初始化其成员变量。事实上，仿函数是编译器实现lambda的一种方式。在C++11总可以把lambda做为仿函数的“语法甜点”。


2. 优点：
* 除了具有仿函数的优点外；书写简单，就地定义。所以可以用来代替仿函数。
* 可以利用lambda函数来封装一些代码逻辑，使其不仅具有函数的包装性，也具有就地可见的自说明性。
* lambda可以等同于其他语言中的局部函数，但可读性更好。
* lambda与static inline函数相比并没有性能上的优势，但也不会差。

3. 使用时的注意事项：
* 值传递时，捕获后变量的值一直是不变的。引用传递时，变量保存的是最新的值。(对于按值方式传递的捕捉列表，其传递的值在lambda函数定义的时候就已经决定了。而按引用传递的捕捉列表变量，其传递的值则等于lambda函数调用时的值。)
* 严格的讲，lambda函数并非函数指针。不过C++11标准允许lambda表达式向函数指针的转换，但前提时lambda函数没有捕捉任何变量，且函数指针所示的函数原型，必须跟lambda函数有着相同的调用方式。（**函数指针无法转换为lambda**）

4. lambda与STL
    简化了STL库函数的使用；例如使用for_each时无需定义有名函数了。



### nullptr 与 nullptr_t
1. 问题：
    因为老版本的C/C++直接宏定义NULL为0，所以在函数重载时传入实参NULL,在指针和整型间会出现二义性。
    nullptr是C11/C++11中针对避免NULL二义性的一个方案。nullprt即所谓的“指针空值类型”的的常量。指针空值类型被命名为nullptr_t。
2. NULL与nullptr的区别：
    * NULL不是关键字，而是一个宏定义。
    * nullptr是一个关键字，而且是有指定的类型。（nullptr的类型是通过decltype对nullptr进行推导而得到的）
    * nullptr是程序更加健壮。

3. C++11严格规定了nullptr_t类型与其他数据类型间的关系。
    * 所以定义为nullptr_t类型的数据都是等价的，行为也是完全一致的。
    * nullptr_t类型数据可以隐式转换成任意一个指针类型。
    * nullptr_t类型数据不能转换为非指针类型，即使使用reinterpret_cast<nullptr_t>()的方式也是不可以的。
    * nullptr_t类型数据不适用于算术运算表达式。
    * nullptr_t类型数据可以用于关系运算表达式，但仅能与nullptr_t类型数据或指针类型数据进行比较，当且仅当关系运算符为==、<=、>=等时返回true.

4. 特殊注意事项：
    * nullptr能用于bool表达式中。
    * nullptr的类型时nullptr_t，而不是指针nullptr_t *。
    * nullptr不能做取地址操作。


### 默认函数的控制
1. 问题：
    * 默认无参构造函数
    * 限制默认函数的生成。例如把拷贝构造函数声明为private成员，并且不提供函数实现。这样做会对友元类或函数的使用造成麻烦。友元类很可能需要拷贝构造函数，而简单声明private的拷贝构造函数不实现的话，会导致编译失败。为了避免这种情况，我们还必须提供拷贝构造函数的实现版本，并将其声明为private成员，才能达到需要的效果。**解决方法：C++11中，标准则给出了更为简单的方法，即在函数的定义或者声明加上"=delete",则会指示编译器不生成函数的缺省版本。值得注意的是，一旦缺省版本被删除了，重载该函数也是非法的。**

2. "=default"与"=delete"：
    * "=default"修饰的函数为显示缺省函数，"=delete"修饰的函数为删除函数。引入这个特性的目的是为了增强对类默认函数的控制，让程序员能够更加精细地控制默认版本的函数。
    * "=default"还可以应用于类定义之外修饰成员函数。好处：程序员可以对一个class定义提供多个实现版本。
    * 显示删除还可以避免编译器做一些不必要的隐式数据类型转换。**避免和explicit关键字一起使用，会引起混乱 注意：普通函数也可以用显示参数特性**
3. 特殊用法：
    * 当需要避免在堆上分配class的对象时，可以使用显示删除自定义类型的operator new操作符。
    * 当需要对象在指定内存位置进行内存分配，并且不需要析构函数来完成一些对象级别的清理时。就可以通过显示删除析构函数来限制自定义类型在栈上或者静态的构造。例如，当使用placement new构造对象时，编译器不会为其调用析构函数，因此析构函数被删除的类能够正常地构造。



## 实践总结
* 右值变量也能进行取地址运算。
~~~cpp
const nullptr_t && default_nullptr = nullptr; //default_nullptr是nullptr的一个右值引用。
cout << &default_nullptr << endl; //nullptr是编译时期的关键字，也是一个右值常量，所以不支持取值操作（&nullptr是错误的）
~~~

* 关于void *的一些注意事项
~~~cpp
int *px = (void *)0;//编译错误，不能隐式地将无类型指针转换为int *类型的指针。所以nullptr使用更方便。

sizeof(nullptr_t) == sizeof(void *); //size一样，但是实现上是完全不同的。
~~~

* nullptr 在应用与模板中时，只能把其作为一个普通的类型来进行推导，并不会将其视为T*指针。
~~~cpp
template<typename T> void g(T* t) {}

g(nullptr);//编译失败，nullptr的类型是nullptr_t，而不是指针。
~~~