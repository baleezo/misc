#!/usr/bin/env python
"The Bulls and Cows Game"

EXIT = 'exit'
DIGITS = 3 
ANS_FILE = 'answer.txt'
HIS_FILE = 'history.txt'

class MyError (Exception):
  def __init__(self, value):
    self.value = value
  def __str__(self):
    return repr(self.value)

def open_file(filename, flag):
  try:
    fd = open(filename, flag)
  except:
    if flag == 'r':
      return {'failed':True, 'err_msg':'ERROR: Open input file %s failed' %ANS_FILE}
    elif flag == 'w':
      return {'failed':True, 'err_msg':'ERROR: Open output file %s failed' %HIS_FILE}
  else:
    return {'failed':False, 'fd':fd}

def check_data_format(data_raw, data_set, data_len, source):
  if not data_raw.isdigit():
    return 'ERROR: Some chars of the %s is not digit' %source
  elif len(data_set) != data_len or data_len != DIGITS:
    return 'ERROR: Chars of %s are not exactly %d different digits' %(source, DIGITS)
  else:
    return False

def prompt_and_get_input():
  keybroad_input = raw_input('Guess %d different digits: ' %DIGITS)
  return keybroad_input

def check_exit(keybroad_input):
  if keybroad_input.lower() == EXIT.lower():
    return True
  else:
    return False

def check_guess(ans, ans_set, keybroad_input, keyin_len):
  res = {'A':0, 'B':0}
  for i in range(keyin_len):
    if keybroad_input[i] in ans_set:
      if keybroad_input[i] == ans[i]:
        res['A'] += 1
      else:
        res['B'] += 1
  return res

if __name__ == '__main__':
  ans_fd, his_fd = False, False
  try:
    ans_fd = open_file(ANS_FILE, 'r')
    if ans_fd['failed']:
      raise MyError(ans_fd['err_msg'])
    else:
      input_file = ans_fd['fd']
    # read ans from ANS_FILE
    ans = input_file.read()
    # throw away the newline 
    ans = ans.split('\n')[0]
    ans_len, ans_set = len(ans), set(ans)
    # check ans file input format
    err = check_data_format(ans, ans_set, ans_len, ANS_FILE)
    if err != False:
      raise MyError(err)
    
    his_fd = open_file(HIS_FILE, 'w')
    if his_fd['failed']:
      raise MyError(his_fd['err_msg'])
    else:
      output_file = his_fd['fd']
    # main loop
    while True:
      keybroad_input = prompt_and_get_input()
      keyin_len, keyin_set = len(keybroad_input), set(keybroad_input)
      if check_exit(keybroad_input):
        break
      # check keybroad input format
      err = check_data_format(keybroad_input, keyin_set, keyin_len, 'keybroad input')
      if err != False:
        print err
        continue
      # check user guess result
      res = check_guess(ans, ans_set, keybroad_input, keyin_len)
      print 'Result: %s %dA%dB' %(keybroad_input, res['A'], res['B'])
      try:
        output_file.write('%s %dA%dB\n' %(keybroad_input, res['A'], res['B']))
      except:
        raise MyError('ERROR: Write history to %s failed' %HIS_FILE)
      # if user guessed the right answer, the game is overed
      if res['A'] == DIGITS:
        print 'You win!!!'
        break
  except MyError as e:
    print e.value
  finally:
    if ans_fd:
      if not ans_fd['failed']:
        ans_fd['fd'].close()
    if his_fd:
      if not his_fd['failed']:
        his_fd['fd'].close()
