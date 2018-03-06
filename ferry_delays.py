import csv
import sys
import calendar

def calculateAvg(timeList,terminal):
    total_delay = 0
    total_departures = 0
    for row in timeList:
        if row['departure_terminal'] == terminal:
            total_delay += (float(row['actual_departure_hour']) + float(row['actual_departure_minute'])/60) - (float(row['scheduled_departure_hour']) + float(row['scheduled_departure_minute'])/60)
            total_departures += 1
    avg_delay = 60 * float(total_delay/total_departures)
    return avg_delay


def main():
    argList = []
    for arg in sys.argv[1:]:
        argList.append(arg)
    while True:
        inpTerminal = input("Enter s for Swartz Bay or t for Tsawwassen delay statistics (enter q to quit):")
        if inpTerminal== 'q':
            exit()
        if inpTerminal != 's' and inpTerminal != 't':
            print("Invalid input")
            continue
        else:
            break
    while True:
        inpMonth = input("Enter the number of the month (enter q to quit):")
        if inpMonth == 'q':
            exit()
        if (int(inpMonth) <= 12 and int(inpMonth) >= 1) != True:
            print("Invalid input")
            continue
        else:
            break
    inpMonth = int(inpMonth)
    if inpTerminal == 's':
        term = 'Swartz Bay'
    else:
        term = 'Tsawwassen'
    month = calendar.month_abbr[inpMonth]
    for node in argList:
        csvRead = None
        if month == node[18:21]:
            csvRead = csv.DictReader(open(node))
            break
    if csvRead == None:
        print("RESULTS\n%s:\n   No delay data for %s\nEND" %(term, month))
        exit()
    ferry_delay = calculateAvg(csvRead,term)
    print("RESULTS\n%s:\n   Average delay for %s: %.2f\nEND" %(term, month, ferry_delay))
    main()

if __name__ == '__main__':
    main()
