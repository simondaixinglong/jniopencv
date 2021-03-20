package com.simon.a;

import java.util.Collections;

import javax.naming.ldap.SortControl;

public class Simple1 {
	private static String name;// һ��ѱ���
	private static String name1;// һ��ѱ���
	private static String name3;// һ��ѱ���

	static {
		System.load("C:/Users/hcDarren/Desktop/android/NDK/NDK_Day15_VS/x64/Debug/NDK_Day15_VS.dll");
	}

	public Simple1() {

	}

	public static void main(String[] args) {
		// 1. ���鴦���һЩϸ��
		/*
		 * int[] arr = {11,22,-3,2,4,6,-15};
		 * 
		 * 
		 * sort(arr);
		 * 
		 * for (int i = 0; i < arr.length; i++) { System.out.print(arr[i]+"\t");
		 * }
		 * 
		 * // 2. �ֲ����ú�ȫ������ // localRef();
		 * 
		 * // saveGlobalRef("Darren");
		 * 
		 * // System.out.println(getGlobalRef());
		 * 
		 * // ���ʵ�ʱ��ȥ�ͷ� // delteGlobalRef();
		 * 
		 * // �ٴλ�ȡ // System.out.println(getGlobalRef());
		 * 
		 * // 3.������� static��native����һ��ѷ���Ҫȥ��ȡ name ���� // ��ʼ��ȫ�־�̬����
		 * initStaticCache();
		 * 
		 * staticLocalCache("Darren");
		 * 
		 * System.out.println("name = "+name);
		 * 
		 * staticLocalCache("Jack");// not null
		 * 
		 * System.out.println("name = "+name);
		 * 
		 * staticLocalCache("Rose"); // not null System.out.println("name = "
		 * +name);
		 */

		// �쳣�����򵥽���C++�쳣��

		try {
			exception();
		} catch (NoSuchFieldException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		System.out.println("name3 = " + name3);
	}

	private static final native void exception() throws NoSuchFieldException;

	private static final native void initStaticCache();

	private static final native void staticLocalCache(String name);

	private static final native void delteGlobalRef();

	private static final native String getGlobalRef();

	private static final native void saveGlobalRef(String str);

	private static final native void localRef();

	private static final native void sort(int[] arr);

}
