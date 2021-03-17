package com.shengsiyuan.kotlin5

/*
    内联函数（inline function）
    将方法体原封不动的copy到调用的地方
    有几次调用，就copy几个方法体
 */

inline fun myCalculate(a: Int, b: Int) = a + b

fun main(args: Array<String>) {
    println(myCalculate(1, 2))
}