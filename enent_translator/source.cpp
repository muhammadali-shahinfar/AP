#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#define seperator ' '
const char* NO_TRANSLATOR_FOUND = "Not found";
using namespace std;
struct times {
	int hour;
	int minute;
};
struct span {
	times start_time;
	times end_time;
};
struct language {
	string language_name;
	string translator_name = NO_TRANSLATOR_FOUND;
};
struct translator {
	string name;
	vector<span> free_times;
	vector<language> know_languages;
};
struct event {
	string name;
	span event_time;
	vector<language> talked_language;

};
typedef vector<span> spans_vector;
typedef vector<translator> translators_vector;
typedef vector<event> events_vector;
typedef vector<string> names_of_language_translator;
void sort_translators_alphabetical(translators_vector &translators) {
	for (int i = 0; i < translators.size(); i++) {
		for (int j = i + 1; j < translators.size(); j++) if (translators[i].name.compare(translators[j].name) > 0) {
			translator translator_tmp = translators[i];
			translators[i] = translators[j];
			translators[j] = translator_tmp;
		}
	}
}
bool is_know(translator choosen_translator, language choosen_language) {
	for (int i = 0; i < choosen_translator.know_languages.size(); i++) {
		if (choosen_language.language_name.compare(choosen_translator.know_languages[i].language_name) == 0) return true;
	}
	return false;
}
bool is_after(times first_time, times second_time) {
	if (first_time.hour > second_time.hour) return true;
	if (first_time.hour == second_time.hour && first_time.minute > second_time.minute) return true;
	return false;
}
bool is_before(times first_time, times second_time) {
	if (first_time.hour < second_time.hour) return true;
	if (first_time.hour == second_time.hour && first_time.minute < second_time.minute) return true;
	return false;
}
bool is_have_free_time(translator choosen_translator, span event_time) {
	for (int i = 0; i < choosen_translator.free_times.size(); i++) {
		if (is_after(event_time.start_time, choosen_translator.free_times[i].start_time) && is_before(event_time.end_time, choosen_translator.free_times[i].end_time)) {
			return true;
		}
	}
	return false;
}
bool is_translator_exist(language choosen_language) {
	if (choosen_language.translator_name.compare(NO_TRANSLATOR_FOUND) == 0) return false;
	return true;
}
int number_of_language_translator(language choosen_language, translators_vector translators) {
	int number_of_language_translators = 0;
	for (int i = 0; i < translators.size(); i++) {
		for (int j = 0; j < translators[i].know_languages.size(); j++) if (translators[i].know_languages[j].language_name == choosen_language.language_name) number_of_language_translators++;
	} // typrdef translators[i].know_languages
	return number_of_language_translators;
}
translators_vector find_translator(language un_employed_language, translators_vector translators, span event_time) {
	translators_vector correct_translators;
	for (int i = 0; i < translators.size(); i++) {
		if (is_know(translators[i], un_employed_language)) {
			if (is_have_free_time(translators[i], event_time)) {
				correct_translators.push_back(translators[i]);
			}
		}
	}
	return correct_translators;
}
void sort_translator_by_language(translators_vector& translators) {
	for (int i = 0; i < translators.size(); i++) {
		for (int j = i + 1; j < translators.size(); j++) if (translators[i].know_languages.size()>translators[j].know_languages.size()) {
			swap(translators[i], translators[j]);
		}
	}
}
translator choose_best_translator(translators_vector &translators, span event_time) {
	sort_translators_alphabetical(translators);
	sort_translator_by_language(translators);
	for (int j = 0; j < translators.size(); j++) {
		if (is_have_free_time(translators[j], event_time)) return translators[j];
	}
	translator NULL_translator;
	return NULL_translator;
}
void find_best_language(event working_events, int &working_language_index, translators_vector translators) {
	int min_translator_of_languages = translators.size() + 1;
	for (int i = 0; i < working_events.talked_language.size(); i++) {
		int num_of_language_translator = number_of_language_translator(working_events.talked_language[i], translators);
		if (num_of_language_translator < min_translator_of_languages && !is_translator_exist(working_events.talked_language[i])) {
			min_translator_of_languages = num_of_language_translator;
			working_language_index = i;
		}
	}
}
int find_translator_index_by_name(string translator_name, translators_vector translators) {
	for (int i = 0; i < translators.size(); i++) {
		if (!translators[i].name.compare(translator_name)) return i;
	}
	cout << "we havnt this name: " << translator_name << endl;
	return 0;
}
void fill_translator_time(translators_vector& translators, span event_time, string choosen_translator_name) {
	int choosen_translator_index = find_translator_index_by_name(choosen_translator_name, translators);
	int free_time_index;
	for (free_time_index = 0; free_time_index < translators[choosen_translator_index].free_times.size(); free_time_index++) {
		if (is_have_free_time(translators[choosen_translator_index], event_time)) {
			continue;
		}
	}
	span new_free_time = { event_time.end_time,translators[choosen_translator_index].free_times[free_time_index].end_time };
	translators[choosen_translator_index].free_times[free_time_index].end_time = event_time.start_time;
	translators[choosen_translator_index].free_times.insert(translators[choosen_translator_index].free_times.begin() + free_time_index + 1, new_free_time);
}
event devote_translator(event &working_event, translators_vector &translators) {
	int working_language_index;
	for (int i = 0; i < working_event.talked_language.size(); i++) {
		find_best_language(working_event, working_language_index, translators);
		translators_vector correct_translators = find_translator(working_event.talked_language[working_language_index], translators, working_event.event_time);
		if (correct_translators.size() == 0)continue;
		string choosen_translator_name = choose_best_translator(correct_translators, working_event.event_time).name;
		working_event.talked_language[working_language_index].translator_name = choosen_translator_name;
		fill_translator_time(translators, working_event.event_time, choosen_translator_name);
	}
	return working_event;
}
events_vector devote_translator_to_events(events_vector events, translators_vector translators) {
	events_vector new_events;
	for (int i = 0; i < events.size(); i++) {
		new_events.push_back(devote_translator(events[i], translators));
	}
	return new_events;
}
int char2_to_int(char first_number, char second_number) {
	int number = first_number - '0';
	number *= 10;
	number += second_number - '0';
	return number;

}
times input_time(string time_string) {
	times new_time;
	new_time.hour = char2_to_int(time_string[0], time_string[1]);
	new_time.minute = char2_to_int(time_string[3], time_string[4]);
	return new_time;
}
void input_translator_time(stringstream& translator_data, span& translator_free_time) {
	string time_string;
	getline(translator_data, time_string, seperator);
	translator_free_time.start_time = input_time(time_string);
	getline(translator_data, time_string, seperator);
	translator_free_time.end_time = input_time(time_string);
}
void input_languages_for_translator(stringstream& translator_data, translator& new_translator) {
	string language_name;
	while (getline(translator_data, language_name, seperator)) {
		language new_language;
		new_language.language_name = language_name;
		new_translator.know_languages.push_back(new_language);

	}
}
translator input_translator(string translator_data_string) {
	stringstream translator_data(translator_data_string);
	translator new_translator;
	string new_translator_name;
	span translator_free_time;
	getline(translator_data, new_translator_name, seperator);
	new_translator.name = new_translator_name;
	input_translator_time(translator_data, translator_free_time);
	input_languages_for_translator(translator_data, new_translator);
	new_translator.free_times.push_back(translator_free_time);
	return new_translator;
}
void input_event_name(stringstream& event_data, event& new_event) {
	string new_event_name;
	getline(event_data, new_event_name, seperator);
	new_event.name = new_event_name;
}
void input_event_time(stringstream& event_data, event& new_event) {
	string time_string;
	getline(event_data, time_string, seperator);
	new_event.event_time.start_time = input_time(time_string);
	getline(event_data, time_string, seperator);
	new_event.event_time.end_time = input_time(time_string);
}
void input_event_language(stringstream& event_data, event& new_event) {
	string language_name;
	while (getline(event_data, language_name, seperator)) {
		language new_language;
		new_language.language_name = language_name;
		new_event.talked_language.push_back(new_language);
	}
}
event input_events(string event_data_string) {
	stringstream event_data(event_data_string);
	event new_event;
	input_event_name(event_data, new_event);
	input_event_time(event_data, new_event);
	input_event_language(event_data, new_event);
	return new_event;
};
void add_translator(ifstream& input_file, translators_vector &translators) {
	string translator_data;
	getline(input_file, translator_data);
	translator translator_tmp = input_translator(translator_data);
	translators.push_back(translator_tmp);
}
void add_event(ifstream& input_file, events_vector& events) {
	string event_data;
	getline(input_file, event_data);
	event event_tmp = input_events(event_data);
	events.push_back(event_tmp);
}
void input_datas_from_file(char* file_name, translators_vector &translators, events_vector &events) {
	ifstream input_file(file_name);
	string tmp;
	int translators_number, event_number;
	input_file >> translators_number;
	getline(input_file, tmp);
	for (int i = 0; i < translators_number; i++) {
		add_translator(input_file, translators);
	}
	input_file >> event_number;
	getline(input_file, tmp);
	for (int i = 0; i < event_number; i++) {
		add_event(input_file, events);
	}
	input_file.close();
}
void output_language(language choosen_language) {
	cout << choosen_language.language_name << ": " << choosen_language.translator_name << endl;
}
void output_event(event choosen_event) {
	cout << choosen_event.name << endl;
	for (int i = 0; i < choosen_event.talked_language.size(); i++) {
		output_language(choosen_event.talked_language[i]);
	}
}
void output(events_vector events) {
	for (int i = 0; i < events.size(); i++) {
		output_event(events[i]);
	}
}
int main(int argc, char* argv[]) {
	translators_vector translators;
	events_vector events;
	input_datas_from_file(argv[1], translators, events);
	events = devote_translator_to_events(events, translators);
	output(events);

}
