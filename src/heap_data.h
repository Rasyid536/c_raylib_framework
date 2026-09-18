#pragma once
#include <stddef.h>
#include <stdint.h>

#define DECLARE_VECTOR(T) \
    typedef struct { \
        T *data; \
        size_t length; \
        size_t capacity; \
    } Heap_Data_##T; \
    \
    void addend_##T(Heap_Data_##T *vector, T value); \
    void pop_##T(Heap_Data_##T *vector); \
    void insert_##T(Heap_Data_##T *vector, size_t index, T value); \
    void addbegin_##T(Heap_Data_##T *vector, T value); \
    void shift_##T(Heap_Data_##T *vector); \
    void replace_##T(Heap_Data_##T *vector, size_t index, T value);


// DEFINE_VECTOR(T) akan men-generate logika persis seperti kode asli kamu.
#define DEFINE_VECTOR(T) \
    void addend_##T(Heap_Data_##T *vector, T value) { \
        if (vector->length >= vector->capacity) { \
            if (vector->length == 0) { \
                vector->capacity = 2; \
            } else { \
                vector->capacity *= 2; \
            } \
            T *temp = realloc(vector->data, vector->capacity * sizeof(T)); \
            if (temp == NULL) { \
                printf("failed to realloc memory\n"); \
                return; \
            } \
            vector->data = temp; \
        } \
        vector->data[vector->length] = value; \
        ++vector->length; \
    } \
    \
    void pop_##T(Heap_Data_##T *vector) { \
        if (vector->length == 0) { \
            return; \
        } \
        --vector->length; \
        if (vector->length < vector->capacity / 2) { \
            if (vector->length == 0) { \
                vector->capacity = 2; \
            } else { \
                vector->capacity /= 2; \
            } \
            T *temp = realloc(vector->data, vector->capacity * sizeof(T)); \
            if (temp == NULL) { \
                printf("failed to realloc memory\n"); \
                return; \
            } \
            vector->data = temp; \
        } \
    } \
    \
    void insert_##T(Heap_Data_##T *vector, size_t index, T value) { \
        index -= 1; \
        if (index > vector->length) { \
            printf("can't insert outside length.\n"); \
            return; \
        } \
        vector->length++; \
        for (size_t i = vector->length; i > index; i--) { \
            vector->data[i] = vector->data[i - 1]; \
        } \
        vector->data[index] = value; \
    } \
    \
    void addbegin_##T(Heap_Data_##T *vector, T value) { \
        insert_##T(vector, 1, value); \
    } \
    \
    void shift_##T(Heap_Data_##T *vector) { \
        for (size_t i = vector->length; i > 0; i--) { \
            vector->data[i] = vector->data[i - 1]; \
        } \
    } \
    \
    void replace_##T(Heap_Data_##T *vector, size_t index, T value) { \
        index -= 1; \
        if (index > vector->length) { \
            printf("can't replace outside length.\n"); \
            return; \
        } \
        vector->data[index] = value; \
    }
