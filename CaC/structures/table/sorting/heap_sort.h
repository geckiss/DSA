#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Heap sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class HeapSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Heap sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator) override;
	};

	template<typename K, typename T>
	inline void HeapSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, Comparator<T>* comparator)
	{
		bool vymena;
		int aktualny;
		int otec;
		int max;
		int lavy;
		int pravy;
		for (int i = 1; i < table.size(); i++) {
			aktualny = i;

			do {
				vymena = false;
				otec = (aktualny - 1) / 2;
				if ((aktualny > 0) && (comparator->compare(table.getItemAtIndex(aktualny).accessData(), table.getItemAtIndex(otec).accessData()))) {
				//if ((aktualny > 0) && (table.getItemAtIndex(aktualny).getKey() > table.getItemAtIndex(otec).getKey())) {
					table.swap(table.getItemAtIndex(aktualny), table.getItemAtIndex(otec));
					notify();
					aktualny = otec;
					vymena = true;
				}
			} while (vymena);
		}

		for (int i = table.size() - 1; i > 0; i--) {
			table.swap(table.getItemAtIndex(0), table.getItemAtIndex(i));
			notify();
			aktualny = 0;

			do {
				vymena = false;
				lavy = aktualny * 2 + 1;
				pravy = aktualny * 2 + 2;
				if ((lavy < i) && (pravy < i)) {
					max = comparator->compare(table.getItemAtIndex(lavy).accessData(), table.getItemAtIndex(pravy).accessData()) ? lavy : pravy;
					//max = table.getItemAtIndex(lavy).getKey() > table.getItemAtIndex(pravy).getKey() ? lavy : pravy;
				}
				else {
					max = lavy < i ? lavy : pravy;
				}
				if ((max < i) && (comparator->compare(table.getItemAtIndex(max).accessData(), table.getItemAtIndex(aktualny).accessData()))) {
				//if ((max < i) && (table.getItemAtIndex(max).getKey() > table.getItemAtIndex(aktualny).getKey())) {
					table.swap(table.getItemAtIndex(max), table.getItemAtIndex(aktualny));
					notify();
					aktualny = max;
					vymena = true;
				}
			} while (vymena);
		}
	}

}