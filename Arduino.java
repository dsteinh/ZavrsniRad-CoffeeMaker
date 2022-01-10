package com.example.aktivnosti;

import android.os.AsyncTask;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.net.URI;

public class Arduino extends AsyncTask<String, Integer, String> {

    @Override
    protected String doInBackground(String... urls) {

        try {
            HttpClient httpclient = new DefaultHttpClient();
            HttpGet request = new HttpGet();
            URI website = new URI(urls[0]);
            request.setURI(website);
            HttpResponse response = httpclient.execute(request);
        } catch (Exception e) {
            e.printStackTrace();
            // TODO napravi nešto ako pukne request
        }

        return null;
    }

}
