package com.example.prac5;

public class Item {
    private String text;
    private int imageResId; // ID ресурса изображения

    public Item(String text, int imageResId) {
        this.text = text;
        this.imageResId = imageResId;
    }

    public Item(String text){
        this.text = text;
    }

    public String getText() {
        return text;
    }

    public int getImageResId() {
        return imageResId;
    }
}
