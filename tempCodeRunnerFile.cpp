hile(mergedList){
        cout << mergedList->val << " -> ";
        mergedList = mergedList->next;
    }
    cout << "NULL" << endl;