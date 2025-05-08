package com.example.prac10_1;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import java.util.ArrayList;
import java.util.List;
public class DatabaseHelper extends SQLiteOpenHelper{

    // Информация о базе данных
    private static final String DATABASE_NAME = "ExampleDB";
    private static final int DATABASE_VERSION = 1;

    // Информация о таблице
    public static final String TABLE_NAME = "users";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_NAME = "name";
    public static final String COLUMN_PHONE = "phone";
    public static final String COLUMN_AGE = "age";
    public static final String COLUMN_WEIGHT = "weight";

    // SQL запрос для создания таблицы
    private static final String CREATE_TABLE =
            "CREATE TABLE " + TABLE_NAME + " (" +
                    COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    COLUMN_WEIGHT + " TEXT," +
                    COLUMN_AGE + " TEXT," +
                    COLUMN_NAME + " TEXT, " +
                    COLUMN_PHONE + " TEXT)";
    public DatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_TABLE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_NAME);
        onCreate(db);
    }

    // Поиск контакта по номеру телефона
    public Contact findContact(String phone) {
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.query(TABLE_NAME, new
                        String[]{COLUMN_ID, COLUMN_NAME, COLUMN_PHONE, COLUMN_AGE, COLUMN_WEIGHT},
                COLUMN_PHONE + " = ?", new String[]{phone}, null,
                null, null);
        if (cursor != null && cursor.moveToFirst()) {
            Contact contact = new Contact(cursor.getInt(0),
                    cursor.getString(1), cursor.getString(2),
                    cursor.getString(3), cursor.getString(4));
            cursor.close();
            db.close();
            return contact;
        }
        if (cursor != null) {
            cursor.close();
        }
        db.close();
        return null;
    }

    // Получение всех контактов
    public List<Contact> getAllContacts() {
        List<Contact> contactList = new ArrayList<>();
        SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = db.rawQuery("SELECT * FROM " +
                TABLE_NAME, null);
        if (cursor.moveToFirst()) {
            do {
                Contact contact = new Contact(cursor.getInt(0),
                        cursor.getString(1), cursor.getString(2),
                        cursor.getString(3), cursor.getString(4));
                contactList.add(contact);
            } while (cursor.moveToNext());
        }
        cursor.close();
        db.close();
        return contactList;
    }



    public boolean deleteContact(String phone) {
        SQLiteDatabase db = this.getWritableDatabase();
        int result = db.delete(TABLE_NAME, COLUMN_PHONE + " = ?",
                new String[]{phone});
        db.close();
        return result > 0;
    }

    public boolean addContact(Contact contact) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COLUMN_AGE, contact.getAge());
        cv.put(COLUMN_WEIGHT, contact.getWeight());
        cv.put(COLUMN_NAME, contact.getName());
        cv.put(COLUMN_PHONE, contact.getPhone());
        long result = db.insert(TABLE_NAME, null, cv);
        db.close();
        return result != -1;
    }

    //Обновляем данные
    public boolean updateContact(String oldPhone, String newName, String newPhone, String newAge, String newWeight) {
        SQLiteDatabase db = this.getWritableDatabase();
        ContentValues cv = new ContentValues();
        cv.put(COLUMN_AGE, newAge);
        cv.put(COLUMN_WEIGHT, newWeight);
        cv.put(COLUMN_NAME, newName);
        cv.put(COLUMN_PHONE, newPhone);
        // Обновляем запись, где номер телефона равен oldPhone
        int result = db.update(TABLE_NAME, cv, COLUMN_PHONE + " = ?", new String[]{oldPhone});
                db.close();
        return result > 0;
    }
}


























