package com.shengsiyuan.kotlin13

import java.io.Serializable
import kotlin.reflect.full.superclasses

class MySerializable: Serializable, MyInterface

fun main(args: Array<String>) {
    val mySerializableType = MySerializable::class
    println(mySerializableType.superclasses)
}

interface MyInterface