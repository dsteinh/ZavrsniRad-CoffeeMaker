package com.example.aktivnosti;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.media.Ringtone;
import android.media.RingtoneManager;
import android.net.Uri;
import android.widget.Toast;

import java.util.Timer;
import java.util.TimerTask;

public class AlarmReceiver extends BroadcastReceiver
{

    @Override
    public void onReceive(Context context, Intent intent) {

        Toast.makeText(context, "Alarm! Wake up! Wake up!", Toast.LENGTH_LONG).show();

        Arduino a = new Arduino();
        a.execute("http://192.168.1.20/LED=ON");

        Uri alarmUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_ALARM);
        if (alarmUri == null)
        {
            alarmUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        }
        final Ringtone ringtone = RingtoneManager.getRingtone(context, alarmUri);
        ringtone.play();
        final Timer t = new Timer();
        t.schedule(new TimerTask() {
            public void run() {
                ringtone.stop();
                t.cancel();
                // I recommend not to put finish() in onCreate() method
                //finish();
            }
        }, 30000);

    }

}


