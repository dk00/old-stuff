def CheckOpts(opts, def_opts):
  for att in def_opts.keys():
    opts.setdefault(att, def_opts[att])
    if opts[att] == None:
      return None
  return opts
