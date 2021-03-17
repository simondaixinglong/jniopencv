package com.shengsiyuan.kotlin2

// 泛型（generics），表示变量类型的参数化

class MyGeneric<T>(t: T) {
    var variable: T

    init {
        this.variable = t
    }
}


fun main(args: Array<String>) {
//    var myGeneric: MyGeneric<String> = MyGeneric<String>("helloworld")
    var myGeneric = MyGeneric("helloworld") //借助于kotlin的类型推断

    println(myGeneric.variable)

    println("--------")

    var myClass = MyClass<String, Number>("abc", 2.2)
    myTest(myClass)
}

// 协变（covariant）与逆变（controvariant）

/**
 * 关于协变与逆变的概念及来源

List<Object>
List<String>

List<String> list = new ArrayList();
List<Object> list2 = list; // 编译失败

//List<String> 并不是 List<Object> 的子类型
假如上面的允许，那么可以做下面的操作
list2.add(new Date())
//然而再使用的时候，就会异常
String str = list.get(0);

//使用通配符，限制了泛型的可用类型与Object的关系，没有直接显示的定义类型是什么
List<? extends Object> list ...


interface Collection<E> {
void addAll(Collection<E> items);
}

void copyAll(Collection<Object> to, Collection<String> from) {
to.addAll(from);
}

//表示addAll中添加的只要是E的子类型就可以，而String显然是Object的子类
//在只读取的时候，把类型当做 extends 后面的类型进行处理，这样就产生了协变
interface Collection<E> {
void addAll(Collection<? extends E> items);
}

//协变--获取值
//限制了上界(只能是object，以及object的子类型)
Collection<String>就是Collection<? extends Object>的子类型。
out--出去，只获取

//逆变---写入值
//限制了下界(只能是字符串，以及字符串层次体系上面的类型)
List<? super String>
in--进来，只设置

我们如果只从中读取数据，而不往里面写入内容，那么这样的对象叫做生产者；如果只向里面写入数据，而不从中读取数据，那么这样的数据叫做消费者。

生产者使用? extends E； 消费者使用? super E

 */

class MyClass<out T, in M>(t: T, m: M) {

    private var t: T

    private var m: M

    init {
        this.t = t
        this.m = m
    }

    fun get(): T = this.t

    fun set(m: M) {
        this.m = m
    }
}

fun myTest(myClass: MyClass<String, Number>) {
    var myObject: MyClass<Any, Int> = myClass

    println(myObject.get())
}