package com.shengsiyuan.kotlin6

/*
    闭包
    lambda表达式，匿名函数可以访问外层的变量
 */

fun main(args: Array<String>) {
    var sum = ""

    val strings = arrayOf("hello", "world", "bye")

    strings.filter { it.length > 3 }.forEach {
        sum += it
    }

    println(sum)
}