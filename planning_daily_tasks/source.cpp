#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;
#define ENDING_STRING "#"
#define MINUTE_IN_HOUR 60
struct times {
	int hour;
	int minute;
};
const times STARTING_TIME{ 12, 0 };
const times ENDING_TIME{ 20,0 };
struct span_of_time {
	times begin{ 0,0 };
	times end{ 0,0 };
};
bool operator==(const times time1, const times time2) {
	if (time1.hour == time2.hour&&time1.minute == time2.minute) return 1;
	else return 0;
}
bool operator!=(const times time1, const times time2) {
	if (time1.hour == time2.hour&&time1.minute == time2.minute) return 0;
	else return 1;
}
span_of_time input_number_from_string(string input_string) {
	span_of_time span_of_work_tmp;
	int i = 0;
	while (isdigit(input_string[i])) {
		span_of_work_tmp.begin.hour *= 10;
		span_of_work_tmp.begin.hour += input_string[i] - '0';
		i++;
	}
	i++;
	while (isdigit(input_string[i])) {
		span_of_work_tmp.begin.minute *= 10;
		span_of_work_tmp.begin.minute += input_string[i] - '0';
		i++;
	}
	i++;
	while (isdigit(input_string[i])) {
		span_of_work_tmp.end.hour *= 10;
		span_of_work_tmp.end.hour += input_string[i] - '0';
		i++;
	}
	i++;
	while (isdigit(input_string[i])) {
		span_of_work_tmp.end.minute *= 10;
		span_of_work_tmp.end.minute += input_string[i] - '0';
		i++;
	}
	return span_of_work_tmp;
}
vector <span_of_time> input_meeting() {
	vector <span_of_time> spans_of_meetings;
	string input_string;
	while (cin >> input_string && input_string.compare(ENDING_STRING)) {
		spans_of_meetings.push_back(input_number_from_string(input_string));
	}
	return spans_of_meetings;
}
vector <span_of_time> calculate_free_times_between_meetings(vector <span_of_time> spans_of_meeting) { // correct name
	vector <span_of_time> free_times;
	int i = 0;
	while (i + 1<spans_of_meeting.size()) {
		if (spans_of_meeting[i].end == spans_of_meeting[i + 1].begin);
		else {
			span_of_time tmp_time;
			tmp_time.begin = spans_of_meeting[i].end;
			tmp_time.end = spans_of_meeting[i + 1].begin;
			free_times.push_back(tmp_time);
		}
		i++;
	}
	return free_times;
}
vector <span_of_time> calculate_free_times(vector <span_of_time> spans_of_meeting) {
	vector <span_of_time> free_times;
	free_times = calculate_free_times_between_meetings(spans_of_meeting);
	if (spans_of_meeting[0].begin != STARTING_TIME) {
		span_of_time tmp_time;
		tmp_time.begin = STARTING_TIME;
		tmp_time.end = spans_of_meeting[0].begin;
		free_times.insert(free_times.begin(), tmp_time);
	}
	if (spans_of_meeting[spans_of_meeting.size() - 1].end != ENDING_TIME) {
		span_of_time tmp_time;
		tmp_time.begin = spans_of_meeting[spans_of_meeting.size() - 1].end;
		tmp_time.end = ENDING_TIME;
		free_times.push_back(tmp_time);
	}
	return free_times;
}
vector <vector <int> > input_tasks() {
	vector <vector<int> > tasks;
	int time_of_task, number_of_task_span;
	while (cin >> time_of_task >> number_of_task_span) {
		vector <int> task = { time_of_task,number_of_task_span };
		tasks.push_back(task);
	}
	return tasks;
}
vector <times> convert_int_to_time(vector<vector<int> > tasks) {
	vector <times> times_of_doing_tasks;
	for (int i = 0; i < tasks.size(); i++) {
		times time_of_doing_work_tmp;
		time_of_doing_work_tmp.minute = tasks[i][0] % MINUTE_IN_HOUR;
		time_of_doing_work_tmp.hour = tasks[i][0] / MINUTE_IN_HOUR;
		times_of_doing_tasks.push_back(time_of_doing_work_tmp);
	}
	return times_of_doing_tasks;
}
vector <span_of_time> compute_time_of_doing_tasks(vector <span_of_time> free_times, vector < vector<int> > tasks) {
	vector <span_of_time> times_of_doing_tasks;
	vector <times> times_needed_for_tasks = convert_int_to_time(tasks);
	for (int i = 0; i < tasks.size(); i++) {
		span_of_time time_of_doing_work_tmp;
		time_of_doing_work_tmp.begin = free_times[tasks[i][1] - 1].begin;
		free_times[tasks[i][1] - 1].begin.minute += times_needed_for_tasks[i].minute;
		if (free_times[tasks[i][1] - 1].begin.minute >= MINUTE_IN_HOUR) {
			free_times[tasks[i][1] - 1].begin.hour++;
			free_times[tasks[i][1] - 1].begin.minute -= 60;
		}
		free_times[tasks[i][1] - 1].begin.hour += times_needed_for_tasks[i].hour;
		time_of_doing_work_tmp.end = free_times[tasks[i][1] - 1].begin;
		times_of_doing_tasks.push_back(time_of_doing_work_tmp);
	}
	return times_of_doing_tasks;
}
void print_time_of_doing_tasks(vector <span_of_time> times_of_doing_tasks) {
	for (int i = 0; i < times_of_doing_tasks.size(); i++) {
		cout << i + 1 << "\t" << times_of_doing_tasks[i].begin.hour << ":";
		if (times_of_doing_tasks[i].begin.minute < 10) cout << "0";
		cout << times_of_doing_tasks[i].begin.minute << "-" << times_of_doing_tasks[i].end.hour << ":";
		if (times_of_doing_tasks[i].end.minute < 10) cout << "0";
		else cout << times_of_doing_tasks[i].end.minute << endl;
	}
}
int main() {
	vector <span_of_time> spans_of_meeting;
	vector <span_of_time> free_times;
	vector < vector<int> > tasks;
	vector <span_of_time> times_of_doing_tasks;
	spans_of_meeting = input_meeting();
	free_times = calculate_free_times(spans_of_meeting);
	tasks = input_tasks();
	times_of_doing_tasks = compute_time_of_doing_tasks(free_times, tasks);
	print_time_of_doing_tasks(times_of_doing_tasks);
	return 0;
}
