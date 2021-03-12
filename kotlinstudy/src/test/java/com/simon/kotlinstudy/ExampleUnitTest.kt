package com.simon.kotlinstudy

import org.junit.Test

import org.junit.Assert.*
import java.lang.Exception

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

        //final 类型+类型推断
        val a = 1
        //变量 + 类型推断
        var b = 2

        println("$a + $b = ${a + b}")


        var byte: Byte = 20

        b = byte.toInt()


        //kotlin里面没有三元运算符
        var max = if (a > b) a else b

    }


    /**
     * Int?
     * 可为空
     *
     * Int
     * 不可能为空
     */
    fun convert2Int(string: String): Int? {
        try {
            return string.toInt()
        } catch (e: Exception) {
            return null
        }
    }


    fun convert2Uppercase(string: Any): String? {
        if (string is String) {
            return string.toUpperCase();
        }
        return null
    }


    fun myPrintWhen(string: String): String {
        when (string) {
            "hello" -> return "HELLO"
            "word" -> return "WORD"
            else -> return "other input"
        }
    }

    fun myPrintWhen2(string: String): String = when (string) {
        "hello" -> "HELLO"
        "hello" -> "HELLO"
        "hello" -> "HELLO"
        else -> "other"
    }


}