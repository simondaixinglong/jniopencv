package com.simon.kotlinstudy

import org.junit.Test

import org.junit.Assert.*

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * See [testing documentation](http://d.android.com/tools/testing).
 */
class ExampleUnitTest {
    @Test
    fun addition_isCorrect() {
        val list: List<String> = listOf("a", "b", "c")

//        list.forEach { println(it) }

//        list.forEach { println() }
    }


    /**
     * 有返回值
     */
    fun sum(a: Int, b: Int): Int {
        return a + b
    }


    fun sum1(a: Int, b: Int): Int = a + b

    /**
     * 无返回值
     * 字符串模板
     */
    fun myPrint(a: Int, b: Int): Unit {
        println("$a + $b = ${a + b}")
    }


}