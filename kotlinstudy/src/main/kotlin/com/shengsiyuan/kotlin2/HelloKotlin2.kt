package com.shengsiyuan.kotlin2

/*
    密封类（sealed class）用于父类与子类的一种层次关系，而且是受限的层次关系
    类似于枚举
    1.密封类的子类必须定义在同一个文件中（1.1之前，必须定义在同一个类中）
    2.密封类本身是抽象的
    3.密封类的构造方法是私有的，不允许提供非私有的构造方法

 */

sealed class Calculator

class Add: Calculator()

class Subtract: Calculator()

class Multiply: Calculator()

fun calculate(a: Int, b: Int, cal: Calculator) = when (cal) {
    is Add -> a + b
    is Subtract -> a - b
    is Multiply -> a * b
}

fun main(args: Array<String>) {
    println(calculate(1, 2, Add()))
    println(calculate(1, 2, Subtract()))
    println(calculate(1, 2, Multiply()))
}
