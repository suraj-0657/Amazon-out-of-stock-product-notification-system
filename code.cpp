#include <iostream>
#include<unordered_set>
using namespace std;

class ObserverInterface
{
    public:
    virtual void update() = 0;
};

class StockObservableInterface 
{
    public:
    
    virtual void add (ObserverInterface* obj) = 0;
    virtual void remove (ObserverInterface* obj) = 0;
    virtual void notifyAll (unordered_set<ObserverInterface*> observerlist) = 0;
    virtual void setStockCount(int newStock) = 0;
    virtual int getStockCount() = 0;
};

class IphoneObservable : public StockObservableInterface
{
    unordered_set<ObserverInterface*> observerlist;
    int stockCount;
    
    public:
    
    ~IphoneObservable()
    {
        for(auto observer: observerlist)
            delete observer;
    }
    
    void add (ObserverInterface* obj) 
    {
        observerlist.insert(obj);
    }
    
    void remove (ObserverInterface* obj) 
    {
        observerlist.erase(obj);
    }
    
    void notifyAll (unordered_set<ObserverInterface*> observerlist) 
    {
        for(auto observer : observerlist)
            observer->update();  
    }
    
    void setStockCount (int newStock) 
    {
        if(stockCount == 0)
            notifyAll(observerlist);
        stockCount = stockCount + newStock;
    }
    
    int getStockCount ()
    {
        return stockCount;
    }
    
};

class EmailObserver : public ObserverInterface
{
    string emailId;
    StockObservableInterface *observable;
    
    public:
    
    ~EmailObserver()
    {
        delete observable;
    }
    
    EmailObserver (string emailId, StockObservableInterface *observable)
    {
        this->emailId = emailId;
        this->observable = observable;
    }
    
    void update()
    {
        sendMail (emailId, "Product is in stock back");
    }
    
    void sendMail (string emailId, string msg)
    {
        cout<<"Mail sent to: "<<emailId<<" "<<msg<<endl;
    }
    
};

int main() {
	StockObservableInterface *iphoneObservable = new IphoneObservable;
	ObserverInterface *Rahul = new EmailObserver("rahul@gmail.com", iphoneObservable);
	ObserverInterface *Anil = new EmailObserver("anil@gmail.com", iphoneObservable);
	iphoneObservable->add(Rahul);
	iphoneObservable->add(Anil);
	iphoneObservable->setStockCount(5);
	return 0;
}