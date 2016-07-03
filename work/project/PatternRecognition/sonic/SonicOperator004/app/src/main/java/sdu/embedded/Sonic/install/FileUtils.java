package sdu.embedded.Sonic.install;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class FileUtils {

    public static void deleteFile(File file) {
        if (file.isFile()) file.delete();
        else if (file.isDirectory()) {
            File[] files = file.listFiles();
            for (int i = 0; i < files.length; i++) {
                deleteFile(files[i]);
            }
        }
        file.delete();
    }

    public static void copy(InputStream is, File root, String path) throws IOException {
        File target = new File(root, path);
        if (!target.exists()) target.createNewFile();
        OutputStream os = new FileOutputStream(target);
        byte data[] = new byte[1024];
        int temp = 0;
        while ((temp = is.read(data)) != -1) {
            os.write(data, 0, temp);
        }
        os.flush();
        os.close();
        is.close();
    }


}
