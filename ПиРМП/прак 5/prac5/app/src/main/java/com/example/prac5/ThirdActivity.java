package com.example.prac5;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ThirdActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_third);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        RecyclerView recyclerView = findViewById(R.id.list);
        //Устанавливает макет отображения - гориозонтально
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        // Пример списка строк
        List<Item> items = new ArrayList<>();
        items.add(new Item("Item 1"));
        items.add(new Item("wizard", R.drawable.wizard));

        //Создаем адаптер
        SimpleAdapter adapter = new SimpleAdapter(items);
        //Устанавливаем для спсика адаптер
        recyclerView.setAdapter(adapter);
    }
}
