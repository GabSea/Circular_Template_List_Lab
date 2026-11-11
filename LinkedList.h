//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_LINKEDLIST_H
#define CIRCULARTEMPLATEDLIST_LINKEDLIST_H

#include "Media.h"
#include <iostream>

template<typename media_type>
struct Node {
    // Data is now hard-coded to the BASE CLASS pointer: Media*
    media_type* data;
    Node* next;
    static Media *currentMedia;

    // Constructor initializes data and pointer
    Node(media_type* media) : data(media), next(nullptr) {}
};

// === 5. Hard-coded LinkedList Class (Singly, Non-Circular) ===
// This list is only capable of managing Media* objects (Song*, Podcast*, etc.) and is forward-only.
template<typename media_type>
class LinkedList {
private:
    //Node<media_type>* head;
    Node<media_type>* tail;

public:

    static Node<media_type>* currentMedia;

    // Constructor: Initializes an empty list
    LinkedList() : tail(nullptr) {}

    // Destructor: Cleans up all nodes and the Media objects they point to.
    ~LinkedList() {
        Node<media_type>* current = tail;
        Node<media_type>* next_node = nullptr;

        if (tail != nullptr) {
            current = tail->next;
            tail->next = nullptr;
        }

        // Traverse the list until the end (nullptr) is reached
        while (current != nullptr) {
            next_node = current->next;

            // Delete the Media object stored in the node's data pointer (polymorphic deletion)
            delete current->data;

            // Delete the node itself
            delete current;

            current = next_node;
        }
        tail = nullptr; // Ensure tail is reset
        std::cout << "\n[Playlist cleanup complete. All memory deallocated.]" << std::endl;
    }

    // Insertion: Adds a new Media pointer to the end of the list.
    void insert(Media* newMedia) {
        Node<media_type>* newNode = new Node(newMedia);

        if (tail == nullptr) {
            // Case 1: List is empty. New node becomes the tail.
            tail = newNode;
            tail->next = tail;
            currentMedia = tail;
        } else {
            // Case 2: Adding to the tail and making the new one the tail.
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Traversal: Displays all media items in the list.
    void displayList() const {
        if (tail == nullptr) {
            std::cout << "\n[Playlist is empty.]" << std::endl;
            return;
        }

        std::cout << "\n--- Current Playlist ---" << std::endl;
        Node<media_type>* current = tail->next;
        int index = 1;
        do {
            // Polymorphism in action: calls the specific toString() method for Song or Podcast
            std::cout << index++ << ". " << current->data->toString() << std::endl;
            current = current->next;
        } while (current != tail->next);
        std::cout << "------------------------" << std::endl;
    }

    // Simple play method for demonstration (students will expand this later)
    void playCurrent() const {
        if (currentMedia != nullptr) {
            currentMedia->data->play(); // Calls the virtual play() method
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }

    void playNext() const {
        if (currentMedia != nullptr && currentMedia->next != nullptr) {
            currentMedia = currentMedia->next;
            currentMedia->data->play();
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }
};

template<typename media_type>
Node<media_type> * LinkedList<media_type>::currentMedia = nullptr;

#endif //CIRCULARTEMPLATEDLIST_LINKEDLIST_H