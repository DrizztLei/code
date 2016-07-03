package sdu.embedded.Sonic.install;

import java.io.InputStream;
import java.io.OutputStream;

public class ProcessUtils {

    /**
     * 通过Android底层实现进程关闭
     *
     * @param process
     */
    public static void killProcess(Process process) {
        int pid = getProcessId(process.toString());
        if (pid != 0) {
            try {
                android.os.Process.killProcess(pid);
            } catch (Exception e) {
                try {
                    process.destroy();
                } catch (Exception ex) {
                }
            }
        }
    }

    /**
     * 获取当前进程的ID
     *
     * @param str
     * @return
     */
    public static int getProcessId(String str) {
        try {
            int i = str.indexOf("=") + 1;
            int j = str.indexOf("]");
            String cStr = str.substring(i, j).trim();
            return Integer.parseInt(cStr);
        } catch (Exception e) {
            return 0;
        }
    }


    /**
     * 关闭进程的所有流
     *
     * @param process
     */
    public static void closeAllStream(Process process) {
        try {
            InputStream in = process.getInputStream();
            if (in != null)
                in.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
            InputStream in = process.getErrorStream();
            if (in != null)
                in.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        try {
            OutputStream out = process.getOutputStream();
            if (out != null)
                out.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 销毁一个进程
     *
     * @param process
     */
    public static void processDestroy(Process process) {
        if (process != null) {
            try {
                if (process.exitValue() != 0) {
                    closeAllStream(process);
                    killProcess(process);
                }
            } catch (IllegalThreadStateException e) {
                closeAllStream(process);
                killProcess(process);
            }
        }
    }


    /**
     * 通过线程进行异步销毁
     *
     * @param process
     */
    public static void asyncProcessDestroy(final Process process) {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                processDestroy(process);
            }
        });
        thread.setDaemon(true);
        thread.start();
    }
}