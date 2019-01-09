import os


DAYS = 10
DATA_FILE = os.environ['SO_StockData']


def main():
    with open(DATA_FILE, 'r') as f:
        saved_file = f.read().split('\n')

    new_stock_file = []
    days_of_stock = False
    days_removed = 0

    # Run the simulation for DAYS days
    for i in range(DAYS):
        del new_stock_file[:]

        # Create a new DATA_FILE
        with open(DATA_FILE, 'w') as f:
            for line in saved_file:
                if '}' in line:
                    days_of_stock = False
                    days_removed = 0
                    new_stock_file.append(line)

                elif days_of_stock:
                    days_removed += 1

                    # Once we've removed enough dates, output to the file
                    if days_removed >= DAYS - i - 1:
                        new_stock_file.append(line)

                elif '{' in line:
                    days_of_stock = True
                    new_stock_file.append(line)

            f.write('\n'.join(new_stock_file))

        # Run the trader
        os.system('./ProgramTrader')


if __name__ == '__main__':
    main()
