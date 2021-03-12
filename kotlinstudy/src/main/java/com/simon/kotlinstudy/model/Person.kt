package com.simon.kotlinstudy.model

/**
 * Author: simon
 * Description:
 * Date: 2021/3/10 3:24 PM
 * Version:1.0
 *
 * 跟java相比较，构造方法拆开了
 * 1.定义构造方法，传参
 * 2.在init代码块中给成员变量赋值
 *
 *
 */
class Person constructor(username: String) {

    private var username: String
    private var address: String
    private var age: Int

    init {
        this.username = username
        this.address = "abc"
        this.age = 20
    }

    /**
     * secondary构造方法必须直接或者间接的调用primary构造方法
     */
    constructor(username: String, age: Int) : this(username) {
        this.username = username
        this.age = age
        this.address = "abc"
    }

    constructor(username: String, age: Int, address: String) : this(username, age) {
        this.address = address
    }

    fun printInfo() {
        println("username:$username, age:$age, address:$address")
    }

}

fun main() {

    var person: Person = Person("simon")
    var person1: Person = Person("simon", 10)
    var person2: Person = Person("simon", 30, "sichuan")

    person.printInfo()
    person1.printInfo()
    person2.printInfo()
}


open class Fruit {
    open fun name() {
        println("fruit");
    }
}

class Apple : Fruit() {
    override fun name() {

    }
}

open class MyClass3 {

    open fun method() {
        println("aaa")
    }

    open val name: String get() = "parent"
}















