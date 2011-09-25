
env = Environment()

if ARGUMENTS.get('debug', 0):
  env.AppendUnique(CCFLAGS = '-g')

env.Program('autols', Glob('src/*.c'))
