# C++ Primer第五版笔记

主要内容是代码，仅做个参考。当然这篇文章里还有一些相对来说值得重点关注的东西。

## 泛型算法与迭代器

迭代器：
|分类|操作|容器或者迭代器适配器|
|:-|:-|:-|
|输入迭代器 (input iterator)|`==` `!=` `++` `*`(仅用在=右侧) `->`|`istream_iterator`|
|输出迭代器 (output iterator)|`++` `*`(仅用在=左侧) 一般而言`++`和`*`都是无任何操作返回迭代器本身，赋值操作被委托给具体执行的逻辑（`<<`,`push_back`,`push_front`,`insert`）|`ostream_iterator`, `back_inserter`, `front_inserter`, `inserter`|
|前向迭代器 (forward iterator)|`*`可用在=左右两侧(可读可写)|`forward_list`, `unordered_xxx`系列容器| 
|双向迭代器 (bidirectional iterator)|`--`|`list`,`map`,`set`,`multimap`,`multiset`|
|随机访问迭代器 (random-access iterator)|比较(`<`,`<=`,`>=`,`>`),迭代器和数值的计算(`+`,`+=`,`-`,`-=`),两个迭代器的减法计算(`-`),下标(`iter[n]`等价于`*(iter+n)`)|`vector`,`deque`,`string`|

输入迭代器和输出迭代器是同一层级。每一层级都可以用于需要上一层级迭代器的场景，反之则不可。每一层迭代器都支持上一层支持的所有操作。

标准库算法执行过程中不会改变操作的源序列大小（使用插入迭代器在目标序列上可以改变大小），这保证了操作过程中迭代器绝不会失效。

对于链表类型的容器`list`和`forward_list`定义了几个成员函数形式的算法：`sort`,`merge`,`remove`,`reverse`,`unique`，提供特有函数`splice`。行为与`<algorithm>`中同类算法相似，区别是这些算法会修改给定的链表（需要注意迭代器失效问题）。

标准库泛型算法概览：

|算法类型|类型细分|函数|迭代器要求|备注
|:-:|:-:|:-|:-|:-|
|查找算法|简单查找算法|`find` `find_if` `find_if_not` `count` `count_if` `all_of` `any_of` `none_of`|输入迭代器|
||查找重复值算法|`adjacent_find` `search_n`|前向迭代器|
||查找子序列|`search` `find_first_of` `find_end`|两个前向迭代器(除`find_first_of`要求第一个输入为输入迭代器)|
|其他只读算法||`for_each` `mismatch` `equal`|输入均为输入迭代器|
|二分搜索算法||`lower_bound` `upper_bound` `equal_range` `binary_search`|要求前向迭代器，要求系列元素有序|但如果提供随机访问迭代器的话性能会好很多
|写容器元素的算法|只写不读|`fill` `fill_n` `generate` `generate_n`|输出为输出迭代器|
||使用输入迭代器的写算法|`copy` `copy_if` `copy_n` `move` `transform` `replace_copy` `replace_copy_if` `merge`|输入范围是输入迭代器，输出是输出迭代器|`merge`要求输入序列有序。
||使用前向迭代器的写算法|`iter_swap` `swap_ranges` `replace` `replace_if`|要求前向迭代器，向输入序列写入元素|
||使用双向迭代器的写算法|`copy_backward` `move_backward` `inplace_merge`|要求双向迭代器|`_backward`是从后往前拷贝，元素在目标序列和输入序列中顺序相同。`inplace_merge`原地合并两个有序子序列。
|划分与排序算法|划分算法|`is_partitioned` `partition_copy` `partition_point` `stable_partition` `partition`|双向迭代器| 划分排序算法都分为稳定和不稳定版本
||排序算法|`sort` `stable_sort` `is_sorted` `is_sorted_until` `partial_sort` `partial_sort_copy` `nth_element`|随机访问迭代器|`partial_sort` `nth_element`只进行部分排序工作，常用于不需要排序整个序列的场合，工作量更少。
|通用重排操作|使用前向迭代器的重排算法|`remove` `remove_if` `remove_copy` `remove_copy_if` `unique` `unique_copy` `unique_copy_if` `rotate` `rotate_copy`|前向迭代器|基本版本都进行原地操作，`_copy`则将结果拷贝到新序列。`unique`是去除相邻重复元素（可能需要先排序）。
||使用双向迭代器的重排算法|`reverse` `reverse_copy` |双向迭代器|这些算法要反向处理序列，要求双向迭代器。
||使用随机访问迭代器的重排算法|`random_shuffle` `shuffle`|随机访问迭代器|
|排列算法||`is_permutation` `next_permutation` `prev_permutation`|双向迭代器|生成序列的字典序排列，返回bool值指出是否还有下一个或者前一个排列。算法假定序列中所有元素都唯一。
|有序序列集合算法||`includes` `set_union` `set_intersection` `set_difference` `set_symmetric_difference`|输入为输入迭代器，输出为输出迭代器（如果有的话）|集合包含关系、并集、交集、差集、对称差
|最大最小值|比较元素大小|`min` `max` `minmax` `min_element` `max_element` `minmax_element`|输入迭代器|`min` `max`接受两个数或者一个`initializer_list`。
||字典序比较序列|`lexicographical_compare`|均为输入迭代器|字典序比较两个序列。
|数值算法||`accumulate` `inner_product` `partial_sum` `adjacent_difference` `iota`|输入迭代器|头文件`<numeric>`，`iota`是将一个值依次递增后依次赋给序列的元素。

## 左值、右值、左值引用、右值引用

表达式的两个属性：类型（type）和值类别（value category）。
- 左值引用和右值引用属于类型。
- 左值和右值属于值类别。

值类别的粗略理解（C++11前）：
- 左值：具名变量。
- 右值：临时变量。

值类别准确理解与分类：按照是否拥有身份（have identity）、是否能被移动（movable）对表示的值类别进行分类。
- 拥有身份：可以确定表达式是否与另一表达式指代同一实体（例如通过比较函数或者对象的直接或间接获得的地址）。
- 可被移动：移动构造、移动赋值运算符或者实现移动语义的其他函数重载能够绑定与这个表达式。

左值、右值分类细化：
- 左值（lvalue）：有身份不能移动。
    - 包括：左值表达式结果，返回左值引用函数的返回值，字符串字面量。
    - 用来被赋值，或者当做纯右值来用（使用它的值，如用来给另一个对象赋值）。
    - 性质：可以初始化左值引用，可以使用内建的取地址符取到地址。
- 亡值（xvalue）：有身份能移动。
    - 包括：主要就是`std::move`结果（更一般地，返回右值引用的函数的返回值），或者`static_cast<T&&>(obj)`结果（通常不自己做转换，而是使用`std::move`）。
    - 使用目的就是用来被移动。
    - 性质：见泛左值和右值。特别是，可以是多态的，可以绑定到右值引用。
- 纯右值（prvalue）：无身份能移动。
    - 包括：临时对象，右值表达式结果，其他字面量，返回值类型为非引用的函数返回值，右值的成员等。
    - 用来赋给其他对象，或者被移动。
    - 性质：不具备多态，所以不会是抽象类类型或者其数组，不会是不完全类型（除非位于decltype之中）。

混合类型：
- 泛左值(glvalue)：有身份。包含lvalue和xvalue。
    - 可以自动转化为prvalue（即可以当做纯右值用）。
    - 可以是多态的。
    - 可以是不完整类型，前置声明但未定义的类型。
- 右值(rvalue)：可移动。包含xvalue和prvalue。
    - 是可以移动的表达式。
    - 无法直接使用内建取地址运算符取地址（绑定到右值引用之后可以取地址）。
    - 对内置类型来说不能放在赋值号左边，
    - 可以初始化const左值引用或者右值引用，该右值标识的对象的生命周期被延长到引用的作用域结尾。
    - 可以影响重载，右值可以绑定到const左值引用和右值引用，优先绑定右值引用（移动语义）。

一些要点：
- 字符串字面值是左值，因为可以取地址，其他字面量比如字符字面量则不可。
- C++11之后会自动对函数返回对象（非返回左值或者右值引用的函数）做一个类似于`static_cast<T&&>`的操作，使得返回的局部变量能够变成亡值，使之能够移动，以触发移动语义。编译器会做这个优化。
- 不要对右值调用`std::move()`，（std::move的作用是将左值变为亡值，以用来移动，右值本身就可以移动，不需要再转换）。通常问题不大，但如果将右值转亡值的结果绑定到一个右值引用则会发生右值销毁后引用悬垂的情况（直接将右值绑定到右值引用则不会这样）。

左值引用：
- 别名。

右值引用：
- 延长纯右值的生命周期。
- 右值引用本身是左值（或者说无论左值右值引用都是左值）。
- 右值引用依然是一个引用，不要返回局部变量的引用。

判断一个变量是否是左值和右值引用：
- `std::is_lvalue_reference<decltype(a)>::value`
- `std::is_rvalue_reference<decltype(b)>::value`
- `decltype`会保留所有修饰，包括左值和右值引用，顶层底层const。

比较特殊的表达式的值类别：
- 字符串字面值是左值。其他字面量都是纯右值。
- 枚举值是纯右值，不可取地址。
- 函数名是左值，可以取地址。
- 返回值类型是函数的右值引用的函数调用表示是左值，转换为函数类型右值引用的转型表达式同理。C++11引入，为什么，怎么用不知。（方便取地址，转换为函数指针？）
- this指针是纯右值。不可修改，也不可再取地址。
- lambda表达式是纯右值。
- 右值通过对象取成员`a.m a.*mp`。
- 三元条件表达式`a ? b : c`的最终类型由`b c`决定，可以是左值、亡值、纯右值。

最后：
- `std::move`仅仅只做一个左值（或者右值）到亡值的转换，不创建或绑定任何东西。
- 右值引用基本上只用于函数参数中（其他情况基本都可以视为滥用）。除非使用模板实现类似`std::move`这种东西，否则不应该用于返回值中。
- `return`语句中的局部自动变量被隐式地视为亡值，就算没有RVO/NRVO，移动构造函数也一定会被调用（如果他们存在的话）。见标准`[class.copy] p32`。
    - https://stackoverflow.com/questions/11088023/is-an-object-guaranteed-to-be-moved-when-it-is-returned

参考：
- https://zh.cppreference.com/w/cpp/language/value_category

返回值优化（C++11）：
- 复制消除：https://zh.cppreference.com/w/cpp/language/copy_elision
    - 目的是减少拷贝次数，RVO/NRVO/构造时的复制省略。
    - g++中关闭优化：`-fno-elide-constructors`。
    - 可能会有副作用，但这通常意味着你的设计存在问题。
- https://stackoverflow.com/questions/4986673/c11-rvalues-and-move-semantics-confusion-return-statement

