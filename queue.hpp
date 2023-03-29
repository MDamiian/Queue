#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

template <class T>
class Queue {
///forward definition
    class Node;
  private:
    class Node {
      private:
        T* dataPtr;
        Node* prev;
        Node* next;

      public:
        class Exception : public std::exception {
          private:

            std::string msg;

          public:

            explicit Exception(const char* message) : msg(message) { }

            explicit Exception(const std::string& message) : msg(message) { }

            virtual ~Exception() throw () { }

            virtual const char* what() const throw () {
              return msg.c_str();
              }
          };

      public:
        Node();
        Node(const T&);
        ~Node();

        T* getDataPtr() const;
        T getData() const;
        Node* getPrev() const;
        Node* getNext() const;

        void setDataPtr(T*);
        void setData(const T&);
        void setNext(Node*);
        void setPrev(Node*);
      };

    Node* header;

    void copyAll(const Queue<T>&);

    void deleteAll();

  public:
    class Exception : public std::exception {
      private:

        std::string msg;

      public:

        explicit Exception(const char* message) : msg(message) { }

        explicit Exception(const std::string& message) : msg(message) { }

        virtual ~Exception() throw () { }

        virtual const char* what() const throw () {
          return msg.c_str();
          }
      };

  public:
    Queue();
    Queue(const Queue&);
    ~Queue();

    bool isEmpty();

    void enqueue(const T&);

    T dequeue();

    T getFront();

    Queue& operator = (const Queue&);
  };

///Implementacion

using namespace std;

///Node

template<class T>
Queue<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) { }

template<class T>
Queue<T>::Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr) {
  if(dataPtr == nullptr) {
    throw Exception("Memoria no disponible, Queue<T>::Node::Node");
    }
  }

template<class T>
Queue<T>::Node::~Node() {
  delete dataPtr;
  }

template<class T>
T Queue<T>::Node::getData() const {
  if(dataPtr == nullptr) {
    throw Exception("Dato inexistente, T Queue<T>::Node::getData");
    }
  return *dataPtr;
  }

template<class T>
T* Queue<T>::Node::getDataPtr() const {
  return dataPtr;
  }

template<class T>
typename Queue<T>::Node* Queue<T>::Node::getNext() const {
  return next;
  }

template<class T>
typename Queue<T>::Node* Queue<T>::Node::getPrev() const {
  return prev;
  }

template<class T>
void Queue<T>::Node::setData(const T& e) {
  if(dataPtr == nullptr) {
    if((dataPtr = new T(e)) == nullptr) {
      throw Exception("Memoria no disponible, Queue<T>::Node::setData");
      }
    }
  else {
    *dataPtr = e;
    }
  }

template<class T>
void Queue<T>::Node::setDataPtr(T* p) {
  dataPtr = p;
  }

template<class T>
void Queue<T>::Node::setNext(Node* p) {
  next = p;
  }

template<class T>
void Queue<T>::Node::setPrev(Node* p) {
  prev = p;
  }

///Queue
template<class T>
void Queue<T>::copyAll(const Queue<T>& q) {
  Node* aux(q.header->getNext());
  Node* newNode;

  while(aux != q.header) {
    try {
      if((newNode = new Node(aux->getData())) == nullptr) {
        throw Exception("Memoria no disponible, Queue<T>::copyAll");
        }
      }
    catch(typename Node::Exception ex) {
      throw Exception(ex.what());
      }

    newNode->setPrev(header->getPrev());
    newNode->setPrev(header);

    header->getPrev()->setNext(newNode);
    header->setPrev(newNode);

    aux = aux->getNext();
    }
  }

template<class T>
void Queue<T>::deleteAll() {
  Node* aux;

  while(header->getNext() != header) {
    aux = header->getNext();

    header->setNext(aux->getNext());

    delete aux;
    }

  header->setPrev(header);
  }

template<class T>
Queue<T>::Queue() : header(new Node) {
  if(header == nullptr) {
    throw Exception("Memoria no disponible, Queue<T>::Queue");
    }

  header->setPrev(header);
  header->setNext(header);
  }

template<class T>
Queue<T>::Queue(const Queue& q) : Queue() {
  copyAll(q);
  }

template<class T>
Queue<T>::~Queue() {
  deleteAll();

  delete header;
  }

template<class T>
bool Queue<T>::isEmpty() {
  return header->getNext() == header;
  }

template<class T>
void Queue<T>::enqueue(const T& e) {
  Node* aux;

  try {
    if((aux = new Node(e)) == nullptr) {
      throw Exception("Memoria no disponible, Queue<T>::enqueue");
      }
    }
  catch (typename Node::Exception ex) {
    throw Exception(ex.what());
    }

  aux->setPrev(header->getPrev());
  aux->setNext(header);

  header->getPrev()->setNext(aux);
  header->setPrev(aux);
  }

template<class T>
T Queue<T>::dequeue() {
  if(isEmpty()) {
    throw Exception("Insuficiendi de datos, Queue<T>::dequeue");
    }

  T result(header->getNext()->getData());

  Node* aux(header->getNext());

  aux->getPrev()->setNext(aux->getNext());
  aux->getNext()->setPrev(aux->getPrev());

  delete aux;

  return result;
  }

template<class T>
T Queue<T>::getFront() {
  if(isEmpty()) {
    throw Exception("Insuficiencia de datos, Queue<T>::getFront");
    }

  return header->getNext()->getData();
  }

template<class T>
Queue<T>& Queue<T>::operator = (const Queue& q) {
  deleteAll();

  copyAll(q);

  return *this;
  }

#endif // QUEUE_HPP_INCLUDED
