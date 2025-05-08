package com.example.prac9;

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
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public class MainActivity extends AppCompatActivity {
    EditText file_name_text;
    EditText file_data_text;
    TextView file_read_data;
    AlertDialog dialog;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        Button save_button = findViewById(R.id.save_button);
        Button read_button = findViewById(R.id.read_button);
        Button delete_button = findViewById(R.id.delete_button);
        Button add_button = findViewById(R.id.add_button);
        file_name_text = findViewById(R.id.file_name_text);
        file_data_text = findViewById(R.id.file_data_text);
        file_read_data = findViewById(R.id.file_read_data);
        save_button.setOnClickListener(v -> save_file(v));
        read_button.setOnClickListener(v -> read_file(v));
        delete_button.setOnClickListener(v -> {builder.setMessage("Вы действительно хотите удалить файл " + file_name_text.getText().toString() + "?");
            dialog = builder.create();
            dialog.show();});
        add_button.setOnClickListener(v -> add_data(v));
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

    public void add_data(View v){
        String file_name = file_name_text.getText().toString();
        try (FileOutputStream fos = this.openFileOutput(file_name,
                Context.MODE_APPEND)){
            fos.write(('\n' + file_data_text.getText().toString()).getBytes());
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    public void delete_file(){
        String file_name = file_name_text.getText().toString();
        File dir = getFilesDir();
        File file = new File(dir, file_name);
        boolean deleted = file.delete();
        Toast.makeText(this, deleted + "", Toast.LENGTH_LONG).show();
    }

    public void read_file(View v){
        String file_name = file_name_text.getText().toString();
        try (FileInputStream fis = MainActivity.this.openFileInput(file_name)){
            InputStreamReader inputStreamReader = new InputStreamReader(fis,
                    StandardCharsets.UTF_8);
            StringBuilder stringBuilder = new StringBuilder();
            try (BufferedReader reader = new BufferedReader(inputStreamReader)){
                String line = reader.readLine();
                while (line != null){
                    stringBuilder.append(line).append('\n');
                    line = reader.readLine();
                }
            } catch (IOException e){
                e.printStackTrace();
            }
            String contents = stringBuilder.toString();
            file_read_data.setText(contents);
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    public void save_file(View v){
        String file_name = file_name_text.getText().toString();
        try (FileOutputStream fos = this.openFileOutput(file_name,
                Context.MODE_PRIVATE)){
            fos.write(file_data_text.getText().toString().getBytes());
        } catch (IOException e){
            e.printStackTrace();
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        // Сохраняем значение строковой переменной
        outState.putString("KEY_STATE", "some state");
    }


    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        // Восстанавливаем сохраненное состояние
        String state = savedInstanceState.getString("KEY_STATE");
        // Используем сохраненное значение для восстановления состояния UI или других компонентов
    }

}