# Flight Information System

This project processes flight data, specifically focusing on the arrivals and departures of flights. It reads data from text files, extracts relevant information, and outputs near-future flights in both a text file and console. The system includes functionality for sorting and filtering flights based on time, and is divided into functions that handle both arrivals and departures.

## Features

- **Flight Data Parsing**: Reads flight data from text files (`flights_arrival.txt` and `flights_departure.txt`).
- **Time-based Filtering**: Filters flights arriving or departing within a 60-minute window from the provided time.
- **Data Output**: Outputs near-future flight information to a file (`near_flights_arrival.txt` / `near_flights_depature.txt`) and prints it to the console.
- **Flight Struct Conversion**: Converts raw flight data from text to structured formats for easier processing.
- **Support for Delayed and Multiple Time Entries**: Handles cases where flight times are delayed or multi-part names are used.

## File Structure

- `flights_arrival.txt`: Contains the list of flight arrival details.
- `flights_depature.txt`: Contains the list of flight departure details.
- `near_flights_arrival.txt`: Output file for near-future arrivals.
- `near_flights_depature.txt`: Output file for near-future departures.

## Functions

### 1. **`main_flights_arrival_2_near_flights`**
   - **Description**: Reads the `flights_arrival.txt`, processes it, and filters out the near-future flights based on the given time.
   - **Input**: `time_str` (Time in `HH:MM` format to filter flights).
   - **Output**: Outputs near-future flight arrival details to `near_flights_arrival.txt` and the console.

### 2. **`main_flights_depature_2_near_flights`**
   - **Description**: Reads the `flights_depature.txt`, processes it, and filters out the near-future flights based on the given time.
   - **Input**: `time_str` (Time in `HH:MM` format to filter flights).
   - **Output**: Outputs near-future flight departure details to `near_flights_depature.txt` and the console.

### 3. **`struct_2_file_and_print`**
   - **Description**: Converts an array of `near_flight` structs to a file and prints the data to the console.
   - **Input**: `near_flights[]` (Array of near-future departure flights), `num_near_flights` (Number of near-future flights).
   - **Output**: Writes near-future departure flights to `near_flights_depature.txt` and prints them to the console.

### 4. **`struct_2_file_and_print2`**
   - **Description**: Converts an array of `near_flight` structs to a file and prints the data to the console.
   - **Input**: `near_flights[]` (Array of near-future arrival flights), `num_near_flights` (Number of near-future flights).
   - **Output**: Writes near-future arrival flights to `near_flights_arrival.txt` and prints them to the console.

### 5. **`list_near_flights_depature`**
   - **Description**: Filters departure flights from the `flights_departure` array based on proximity to the given time.
   - **Input**: `flights[]` (Array of flight departure data), `time[]` (The current time in `HH:MM` format).
   - **Output**: Populates the `near_flights[]` array with flights departing within 60 minutes from the given time.

### 6. **`list_near_flights_depature2`**
   - **Description**: Filters arrival flights from the `flights_arrival` array based on proximity to the given time.
   - **Input**: `flights[]` (Array of flight arrival data), `time[]` (The current time in `HH:MM` format).
   - **Output**: Populates the `near_flights[]` array with flights arriving within 60 minutes from the given time.

### 7. **`str_time_2_int_time`** and **`const_str_time_2_int_time`**
   - **Description**: Converts a string time (`HH:MM`) to an integer representing the time in minutes.
   - **Input**: `time[]` (Time in `HH:MM` format).
   - **Output**: Returns the time in minutes.

### 8. **`str_2_struct`**
   - **Description**: Converts an array of strings into `flights_departure` struct data.
   - **Input**: `array[][101]` (Array of string data), `size_array` (Size of the input array).
   - **Output**: Fills the `flights[]` array with structured flight departure data.

## Requirements

- C Compiler (e.g., GCC).
- A text editor to modify flight data files.
- The text files (`flights_arrival.txt`, `flights_depature.txt`) should follow the format specified in the code.

## Usage

1. **Prepare the Data Files**: Create or modify the `flights_arrival.txt` and `flights_depature.txt` with flight data in the specified format.
2. **Run the Program**: Compile and run the C program:
   ```bash
   gcc -o flight_system flight_system.c
   ./flight_system
