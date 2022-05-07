# C++ Primer第五版笔记

主要是代码，仅做个参考。和值得记录的东西。

## 泛型算法与迭代器

迭代器：
|分类|操作|容器或者迭代器适配器|
|:-|:-|:-|
|输入迭代器 (input iterator)|== != ++ *(仅用在=右侧) ->|istream_iterator|
|输出迭代器 (output iterator)|++ \*(仅用在=左侧) 一般而言++和\*都是无任何操作返回迭代器本身，赋值操作被委托给具体执行的逻辑（<<,push_back,push_front,insert）|ostream_iterator, back_inserter, front_inserter, inserter|
|前向迭代器 (forward iterator)|*可用在=左右两侧(可读可写)|forward_list, unordered_xxx系列容器| 
|双向迭代器 (bidirectional iterator)|--|list,map,set,multimap,multiset|
|随机访问迭代器 (random-access iterator)|比较(<,<=,>=,>),迭代器和数值的计算(+,+=,-,-=),两个迭代器的减法计算(-),下标(iter[n]等价于*(iter+n))|vector,deque,string|

输入迭代器和输出迭代器是同一层级。每一层级都可以用于需要上一层级迭代器的场景，反之则不可。每一层迭代器都支持上一层支持的所有操作。

标准库算法执行过程中不会改变操作的源序列大小（使用插入迭代器在目标序列上可以改变大小），这保证了操作过程中迭代器绝不会失效。

对于链表类型的容器list和forward_list定义了几个成员函数形式的算法：sort,merge,remove,reverse,unique，提供特有函数splice。行为与`<algorithm>`中同类算法相似，区别是这些算法会修改给定的链表（需要注意迭代器失效问题）。

标准库泛型算法概览：

|算法类型|类型细分|函数|迭代器要求|备注
|:-|:-|:-|:-|:-|
|查找算法|简单查找算法|`find` `find_if` `find_if_not` `count` `count_if` `all_of` `any_of` `none_of`|输入迭代器|
||查找重复值算法|`adjacent_find` `search_n`|前向迭代器|
||查找子序列|`search` `find_first_of` `find_end`|两个前向迭代器(除find_first_of要求第一个要求输入迭代器)|
|其他只读算法||`for_each` `mismatch` `equal`|输入均为输入迭代器|
|二分搜索算法||`lower_bound` `upper_bound` `equal_range` `binary_search`|要求前向迭代器，要求系列元素有序|但如果提供随机访问迭代器的话性能会好很多
|写容器元素的算法|只写不读|`fill` `fill_n` `generate` `generate_n`|输出为输出迭代器|
||使用输入迭代器的写算法|`copy` `copy_if` `copy_n` `move` `transform` `replace_copy` `replace_copy_if` `merge`|输入范围是输入迭代器，输出是输出迭代器|`merge`要求输入序列有序。
||使用前向迭代器的写算法|`iter_swap` `swap_ranges` `replace` `replace_if`|要求前向迭代器，向输入序列写入元素|
||使用双向迭代器的写算法|`copy_backward` `move_backward` `inplace_merge`|要求双向迭代器|`_backward`是从后往前拷贝，元素在目标序列和输入序列中相同。`inplace_merge`原地合并两个有序子序列。
|划分与排序算法|划分算法|`is_partitioned` `partition_copy` `partition_point` `stable_partition` partition|双向迭代器| 划分排序算法都分为稳定和不稳定版本
||排序算法|`sort` `stable_sort` `is_sorted` `is_sorted_until` `partial_sort` `partial_sort_copy` `nth_element`|随机访问迭代器|`partial_sort` `nth_element`只进行部分排序工作，常用于不需要排序整个序列的场合，工作量更少。
|通用重排操作|使用前向迭代器的重排算法|`remove` `remove_if` `remove_copy` `remove_copy_if` `unique` `unique_copy` `unique_copy_if` `rotate` `rotate_copy`|前向迭代器|基本版本都进行原地操作，`_copy`则将结果拷贝到新序列。`unique`是去除相邻重复元素（可能需要先排序）。
||使用双向迭代器的重排算法|`reverse` `reverse_copy` |双向迭代器|这些算法要反向处理序列，要求双向迭代器。
||使用随机访问迭代器的重排算法|`random_shuffle` `shuffle`|随机访问迭代器|
|排列算法||`is_permutation` `next_permutation` `prev_permutation`|双向迭代器|生成序列的字典序排列，返回bool值指出是否还有下一个或者前一个排列。算法假定序列中所有元素都唯一。
|有序序列集合算法||`includes` `set_union` `set_intersection` `set_difference` `set_symmetric_difference`|输入为输入迭代器，输出为输出迭代器（如果有的话）|集合包含、并集、交集、差集、对称差
|最大最小值|比较元素大小|`min` `max` `minmax` `min_element` `max_element` `minmax_element`|输入迭代器|`min` `max`接受两个数或者一个`initializer_list`。
||字典序比较序列|`lexicographical_compare`|均为输入迭代器|字典序比较两个序列。
|数值算法||`accumulate` `inner_product` `partial_sum` `adjacent_difference` `iota`|输入迭代器|头文件`<numeric>`，`iota`是将一个值依次递增后依次赋给序列的元素。