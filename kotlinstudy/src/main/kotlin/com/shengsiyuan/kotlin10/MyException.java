package com.shengsiyuan.kotlin10;

import java.io.IOException;

public class MyException {

    public void myMethod() throws IOException {
        throw new IOException("I/O异常");
    }
}
