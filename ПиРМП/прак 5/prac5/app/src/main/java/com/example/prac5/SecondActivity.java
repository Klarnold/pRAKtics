package com.example.prac5;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Objects;

public class SecondActivity extends AppCompatActivity {
    ArrayList<String> varieties = new ArrayList<String>();
    ArrayList<String> selectedVarieties = new ArrayList<String>();
    ArrayAdapter<String> varietiesAdapter;
    ListView varietyListView;
    View someVariety = null;
    ArrayList<String> globalFruitVarieties = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_second);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
        varietyListView = findViewById(R.id.my_list_view);

        String[] fruitVarieties;

        String selectedFruit = (String) getIntent().getSerializableExtra("selectedFruit");

        if (Objects.equals(selectedFruit, "Яблоки")){
            fruitVarieties = getResources().getStringArray(R.array.applesVariety);
        }
        else if (Objects.equals(selectedFruit, "Груши")) {
            fruitVarieties = getResources().getStringArray(R.array.pearsVariety);
        }
        else {
            fruitVarieties = getResources().getStringArray(R.array.plumsVariety);
        }
        Collections.addAll(varieties, fruitVarieties);
        varietiesAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_multiple_choice, varieties);
        varietyListView.setAdapter(varietiesAdapter);

//        varietiesAdapter.remove("Assol");

        varietyListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                String variety = varietiesAdapter.getItem(position);
                if (varietyListView.isItemChecked(position)) {
                    selectedVarieties.add(variety);
                }
                else
                    selectedVarieties.remove(variety);
            }
        });

        Button addBtn = findViewById(R.id.add);
        Button removeBtn = findViewById(R.id.remove);

        addBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                _add(v);
            }
        });

        removeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                _remove(v);
            }
        });
    }

    public void addVariety(View view){

    }

    public void _add(View view){
        EditText varietyName = findViewById(R.id.newVariety);
        String variety = varietyName.getText().toString();
        if (!variety.isEmpty()){
            varieties.add(variety);
            varietyName.setText("");
            varietiesAdapter.notifyDataSetChanged();
        }
    }

    public void _remove(View view){
        for (int i=0; i<selectedVarieties.size(); i++){
            varieties.remove(selectedVarieties.get(i));
        }
        varietyListView.clearChoices();
        selectedVarieties.clear();
        varietiesAdapter.notifyDataSetChanged();
    }
}