package sdu.embedded.Sonic.core;

import java.util.ArrayList;

public class RRList<E> {
    private ArrayList<E> list = null;
    private int size = 0;
    private int max = 0;
    private int ptr = 0;
    private int mark = 0;

    public RRList(int max) {
        this.max = max;
        list = new ArrayList<E>(max);
    }

    public boolean add(E object) {
        if (size != max) {
            size++;
            ptr = (ptr + 1) % max;
            list.add(object);
        } else {
            list.set(ptr, object);
            ptr = (ptr + 1) % max;
        }
        return true;
    }

    public E get(int index) {
        int a = (ptr - 1 - index + max) % max;
        if (a < size)
            return list.get(a);
        else return list.get(0);
    }

    public int size() {
        return size;
    }


    public void set(int i, E j) {
        int a = (ptr - 1 - i + max) % max;
        if (a < size)
            list.set(a, j);
    }

    public void reset(E e) {
        for (int i = 0; i < size; i++) {
            list.set(i, e);
        }
    }

    public void mark(int i) {
        mark = (ptr - i + 2 * max) % max;
    }

    public int cut_size(int i) {
//		Log.e("cut_size", ""+((ptr + max - mark)%max + 1 - i)+" ptr: "+ptr+" max:"+max+" mark:"+mark);
        return (ptr + 2 * max - mark) % max + 1 - i;
    }

    public E[] cut(E[] arr) {
        int a;
//		String string = "";
        for (int i = 0; i < arr.length; i++) {
            a = (mark + i - 1 + 2 * max) % max;
            arr[i] = list.get(a);
//			string += arr[i]+",";
        }
//		Log.e("simple_data", string);
        return arr;
    }

    @Override
    public String toString() {
        return list.toString();
    }
}