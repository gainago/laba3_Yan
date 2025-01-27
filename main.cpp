#include <QApplication>
#include "MainWindow.h"
#include "Tests.h" // Подключаем тесты

int main(int argc, char *argv[]) {
    // Запуск тестов
    Test_of_GetLastArraySequence();
    Test_of_GetFirst_ArraySequence();
    Test_of_GetLength_ArraySequence();
    Test_of_Get_ArraySequence();
    Test_of_GetSubsequence_ArraySequence();
    Test_of_Append_ArraySequence();
    Test_of_Prepend_ArraySequence();
    Test_of_InsertAt_ArraySequence();
    Test_of_Concat_ArraySequence();
    Test_BinaryTree_GetLength_Int();
    Test_BinaryTree_Get_Int();
    Test_BinaryTree_Insert_Int();
    Test_BinaryTree_DeleteElem_Int();
    Test_BinTree_SearchSubtree_Int();
    Test_BinTree_SubTree_Int();
    Test_BinTree_SearchBool_Int();
    Test_SortedSequence_Add();
    Test_SortedSequence_Get();
    Test_SortedSequence_GetLength();
    Test_SortedSequence_GetFirstAndLast();
    Test_SortedSequence_IsEmpty();
    Test_SortedSequence_IndexOf();
    Test_SortedSequence_GetSubsequence();
    Test_DictionaryOnSequence_Add();
    Test_DictionaryOnSequence_Get();
    Test_DictionaryOnSequence_ContainsKey();
    Test_DictionaryOnSequence_Remove();
    Test_DictionaryOnSequence_GetByIndex();
    Test_SparseVector_Constructor();
    Test_SparseVector_SetAndGet();
    Test_SparseVector_Append();
    Test_CreateHistogram_YearOfBirth() ;
    Test_CreateHistogram_Height();
    Test_CreateHistogram_FirstNameLetter();
    Test_CreateHistogramInt();

    // Инициализация GUI
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Графический интерфейс для программы");
    window.resize(400, 200);
    window.show();

    return app.exec();
}
