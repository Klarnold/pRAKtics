package com.example.prac9_1;

import android.content.Context;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public class MainActivity extends AppCompatActivity {

    EditText file_name_text;
    EditText file_data_text;
    AlertDialog dialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        AlertDialog.Builder builder = new AlertDialog.Builder(this);

        Button save_button = findViewById(R.id.save_button);
        Button delete_button = findViewById(R.id.delete_button);
        Button add_button = findViewById(R.id.add_button);

        file_name_text = findViewById(R.id.file_name_text);
        file_data_text = findViewById(R.id.file_data_text);

        save_button.setOnClickListener(v -> save_file(v));
        delete_button.setOnClickListener(v -> {builder.setMessage("Вы действительно хотите удалить файл " + file_name_text.getText().toString() + "?");
            dialog = builder.create();
            dialog.show();});
        add_button.setOnClickListener(v -> {
            try {
                add_data(v);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        builder.setTitle("Подтверждение удаления файла");

        builder.setPositiveButton("Да", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                delete_file();
            }
        });
        builder.setNegativeButton("Отмена", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                dialog.dismiss();
            }
        });
    }

    public void add_data(View v) throws IOException {
        String file_name = file_name_text.getText().toString();
        File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS);

        if (!dir.exists()){
            dir.mkdirs();
        }

        File file = new File(dir, file_name);
        FileOutputStream fos = new FileOutputStream(file);
        fos.write(file_data_text.getText().toString().getBytes());
        fos.close();
    }

    public void delete_file(){
        String file_name = file_name_text.getText().toString();
        File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS);
        File file = new File(dir, file_name);
        boolean deleted = file.delete();
        Toast.makeText(this, deleted + "", Toast.LENGTH_LONG).show();
    }


    public void save_file(View v){
        String file_name = file_name_text.getText().toString();
        File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS);

        if (!dir.exists()){
            dir.mkdirs();
        }

        File file = new File(dir, file_name);

        try{
            if (!file.exists()){
                boolean created = file.createNewFile();
                if (created){
                    FileWriter writer = new FileWriter(file);
                    writer.append(file_data_text.getText().toString());
                    writer.flush();
                    writer.close();
                }
            }
            else{
                boolean readable = file.canRead();
                boolean writeable = file.canWrite();
            }
        }catch (IOException e){
            e.printStackTrace();
        }
    }

}
