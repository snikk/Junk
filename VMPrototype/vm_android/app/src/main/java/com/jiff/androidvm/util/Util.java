package com.jiff.androidvm.util;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Executor;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * Created by jglenn on 9/9/15.
 */
public class Util {
    private static Executor mExecutor;
    static {
        BlockingQueue<Runnable> workQueue = new LinkedBlockingQueue<Runnable>();
        mExecutor = new ThreadPoolExecutor(1, 20, 60, TimeUnit.SECONDS, workQueue);
    }

    public static void get(final String urlString, final HttpCallback callback) {
        mExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    URL url = new URL(urlString);
                    HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                    int httpCode = conn.getResponseCode();
                    byte[] response = getString(conn.getInputStream());
                    callback.onSuccess((short) httpCode, response);
                } catch (MalformedURLException ex) {
                    callback.onNetworkError();
                } catch (IOException ex) {

                    callback.onNetworkError();
                }
            }
        });
    }

    private static byte[] getString(InputStream stream) throws IOException
    {
        int n = 0;
        int count = 0;
        ByteArrayOutputStream writer = new ByteArrayOutputStream();
        while (-1 != (n = stream.read())) {
            writer.write(n);
            count++;
        }
        return writer.toByteArray();
    }

    public interface HttpCallback {
        void onSuccess(short code, byte[] response);
        void onNetworkError();
    }
}
