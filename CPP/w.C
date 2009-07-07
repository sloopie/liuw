#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>

#include <fstream.h>
#include <stddef.h>
#include <ctype.h>

using namespace std;

typedef pair<short, short> location;
typedef vector<location, allocator> loc;
typedef vector<string, allocator> text;
typedef pair<text*, loc*> text_loc;

class TextQuery {
	public:
		TextQuery() {memset(this, 0, sizeof(TextQuery));}
		static void filter_element(string felems) { filt_elems = felems;}
		void query_text();
		void display_map_text();
		void display_text_locations();
		void doit() {
			retrieve_text();
			separate_word();
			filter_text();
			suffix_text();
			strip_caps();
			build_word_map();
		}
	private:
		void retrieve_text();
		void separate_word();
		void filter_text();
		void suffix_text();
		void suffix_s(string &);
		void strip_caps();
		void build_word_map();
	private:
		vector<string, allocator> *lines_of_text;
		text_loc *text_locations;
		map<string, loc*, 
			less<string>, allocator> *word_map;
		static string filt_elems;
};


string TextQuery::filt_elems("\",.;:!<<)(\\/");

int main()
{
	TextQuery tq;
	tq.doit();
	tq.query_text();
	tq.display_map_text();
}

void 
TextQuery::
retrieve_text()
{
	string file_name;
	cout << "please enter file name: ";
	cin >> file_name;

	ifstream infile(file_name.c_str(), ios::in);
	if (!infile) {
		cerr << "oops! unable to open file "
			<< file_name << " -- bailing out!\n";
		exit(-1);
	}
	else cout << "\n";
	lines_of_text = new vector<string, allocator>;

	while (getline(infile, textline, '\n'))
		lines_of_text->push_back(textline);
}

void
TextQuery::
separate_word()
{
	vector<string, allocator> *words = new vector<string, allocator>;
	vector<location, allocator> *locations = 
		new vector<location, allocator>;

	for (short line_pos = 0; line_pos < lines_of_text->size(); 
			line_pos++) {
		short word_pos = 0;
		string textline = (*line_of_text)[line_pos];
		string::size_type eol = textline.length();
		string::size_type pos = 0, prev_pos = 0;

		while ((pos = textline.find_first_of(' ', pos))
				!= string::npos) {
			words->push_back(textline.substr(prev_pos, pos-prev_pos));
			locations->push_back(make_pair(line_pos, word_pos));
			word_pos++; pos++; prev_pos = pos;
		}

		words->push_back(textline.substr(prev_pos, pos-prev_pos));
		locations->push_back(make_pair(line_pos, word_pos));
	}
	text_locations = new text_loc(words, locations);
}

void
TextQuery::
filter_text()
{
	if (filt_elems.empty())
		return;
	vector<string, allocator> *words = text_locations->first;

	vector<string, allocator>::iterator iter = words->begin();
	vector<string, allocator>::iterator iter_end = words->end();

	while (iter != iter_end) {
		string::size_type pos = 0;
		while ((pos = (*iter).find_first_of(filt_elems, pos))
				!= string::npos)
			(*iter).erase(pos, 1);
		++iter;
	}
}

void
TextQuery::
suffix_text()
{
	vector<string, allocator> *words = text_locations->first;

	vector<string, allocator>::iterator iter = words->begin();
	vector<string, allocator>::iterator iter_end = words->end();

	while (iter != iter_end) {
		if ((*iter).size() <= 3) {
			++iter;
			continue;
		}
		if ((*iter)[(*iter).size()-1] == 's')
			suffix_s(*iter);
		++iter;
	}
}

void
TextQuery::
suffix_s(string &word)
{
	string::size_type spos = 0;
	string::size_type pos3 = word.size() - 3;

	string suffixes("oussisius");

	if (!word.compare(pos3, 3, suffixes, spos, 3) || 
			!word.compare(pos3, 3, suffixes, spos+6, 3) || 
			!word.compare(pos3+1, 2, suffixes, spos+2, 2) || 
			!word.compare(pos3+1, 2, suffixes, spos+4, 2))
		return;
	string ies("ies");
	if (!word.compare(pos3, 3, ies)) {
		word.replace(pos3, 3, 1, 'y');
		return;
	}
	string ses("ses");
	if (!word.compare(pos3, 3, ses)) {
		word.erase(pos3+1, 2);
		return;
	}

	word.erase(pos3+2);

	if (word[pos3+1] == '\'')
		word.erase(pos3+1);
}

void
TextQuery::
strip_caps()
{
	vector<string, allocator> *words = text_locations->first;

	vector<string, allocator>::iterator iter = words->begin();
	vector<string, allocator>::iterator iter_end = words->end();

	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	while (iter != iter_end) {
		string::size_type pos = 0;
		while ((pos = (*iter).find_first_of(caps, pos))
				!= string::npos)
			(*iter)[pos] = tolower((*iter)[pos]);
		++iter;
	}
}

void
TextQuery::
build_word_map()
{
	word_map = new map<string, loc*, less<string>, allocator>;

	typedef map<string, loc*, less<string>, allocator>::value_type 
		value_type;

	typedef map<string, loc*, less<string>, allocator>::defference_type 
		diff_type;

	set<string, less<string>, allocator> exclusion_set;

	ifstream infile("exclusion_set");

	if (!infile) {
		static string default_excluded_words[25] = {
			"the", "and", "but", "that", "then", "are", "been", 
			"can", "can't", "cannot", "could", "did", "for", 
			"had", "have", "him", "his", "her", "its", "into", 
			"were", "which", "when", "with", "would"
		};

		cerr << "warning! unable to open word exclusion file! -- "
			<< "using default set" << endl;
		copy(default_excluded_words, default_excluded_words+25, 
				inserter(exclusion_set, exclusion_set.begin()));
	}
	else
	{
		istream_iterator<string, diff_type>
			input_set(infile), eos;
		copy(input_set, eos, inserter(exclusion_set, exclusion_set.begin()));
	}

	vector<string, allocator> *text_words = text_locations->first;
	vector<location, allocator> *text_locs = text_locations->second;
	register int elem_cnt = text_words->size();
	for (int ix = 0; ix < elem_cnt; ++ix) {
		string textword = (*text_words)[ix];
		if (textword.size() < 3 || 
				exclusion_set.count(textword))
			continue;
		if (!word_map->count((*text_words)[ix])) {
			loc *ploc = new vector<location, allocator>;
			ploc->push_back((*text_locs)[ix]);
			word_map->insert(value_type((*text_words)[ix], ploc));
		}
		else
			(*word_map)[(*text_words)[ix]]->push_back((*text_locs)[ix]);
	}
}

void
TextQuery::
query_text()
{
	string query_text;
	do {
		cout << "enter a word against which to search the text.\n"
			<< "to quit, enter a single character ==> ";
		cin >> query_text;

		if (query_text.size() < 2)
			break;

		string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		string::size_type pos = 0;

		while ((pos = query_text.find_first_of(caps, pos)) 
				!= string::npos)
			query_text[pos] = tolower(query_text[pos]);

		if (!word_map->count(query_text)) {
			cout << "\nSorry, no entries for "
				<< query_text << ".\n\n";
			continue;
		}

		loc *ploc = (*word_map)[query_text];
		set<short, less<short>, allocator> occurrence_lines;
		loc::iterator liter = ploc->begin(), liter_end = ploc->end();
		while (liter != liter_end) {
			occurrence_lines.insert(
					occurrence_lines.end(), (*liter).first);
			++liter;
		}

		register int size = occurrence_lines.size();
		cout << "\n" << query_text
			<< " occurs " << size
			<< (size == 1 ? " time:" : " times:")
			<< "\n\n";

		set<short, less<short>, allocator>::iterator 
			it = occurrence_lines.begin();

		for ( ; it != occurrence_lines.end(); ++it) {
			int line = *it;
			cout << "\t( line "
				<< line+1 << " ) "
				<< (*lines_of_text)[line] << endl;
		}
		cout << endl;
	} while (!query_text.empty());

	cout << "Ok, bye!\n";
}

void
TextQuery::
display_map_text()
{
	typedef map<string, loc*, less<string> allocator> map_text;
	map_text::iterator iter = word_map->begin();
	map_text::iterator iter_end = word_map->end();

	while (iter != iter_end) {
		cout << "word: " << (*iter).first << " (";
		int loc_cnt = 0;
		loc *text_locs = (*iter).second;

		loc::iterator liter = text_locs->begin(), 
			liter_end = text_locs->end();

		while (liter != liter_end) {
			if (loc_cnt)
				cout << ",";
			else ++loc_cnt;

			cout << "(" << (*liter).first
				<< "," << (*liter).second << ")";
			++liter;
		}

		cout << ")\n";
		++iter;
	}
	cout << endl;
}

void
TextQuery::
display_text_locations()
{
	vector<string, allocator> *text_words = text_locations->first;
	vector<string, allocator> *text_locs = text_locations->second;

	register int elem_cnt = text_words->size();

	if (elem_cnt != text_locs->size()) {
		cerr << "oops! internal error" << endl;
		exit(-2);
	}

	for (int ix = 0; ix < elem_cnt; ++ix) {
		cout << "word: " << (*text_words)[ix] << "\t"
			<< "location: ("
			<< (*text_locs)[ix].first << ","
			<< (*text_locs)[ix].second << ")"
			<< endl;
	}
	cout << endl;
}



