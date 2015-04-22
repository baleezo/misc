#!/usr/bin/env python
import cjson
def TranslateRESTPath(path, update_data, len_limit):
    splitted_path = path.strip('/').split('/')
    path_len = len(splitted_path)
    f_update_data = update_data

    if path_len < len_limit:
        print 'Update path error [%s] too short' %path
        return splitted_path, cjson.decode(f_update_data)

    if path_len == len_limit:
        try:
            return splitted_path, cjson.decode(f_update_data)
        except:
            return splitted_path, '{}'

    f_update_data = []
    for i in xrange(len_limit, path_len):
        f_update_data.append('{"')
        f_update_data.append(splitted_path[i])
        f_update_data.append('":')

    if isinstance(update_data, str) and '"' not in update_data:
        update_data = ''.join(['"', update_data, '"'])

    f_update_data.append(update_data)

    for i in xrange(len_limit, path_len):
        f_update_data.append('}')

    f_update_data = ''.join(f_update_data)
    print 'f_updaet_data:', f_update_data
    try:
        f_update_data = cjson.decode(f_update_data)
    except Exception as e:
        print 'error', e
        f_update_data = {}

    return splitted_path, f_update_data

TranslateRESTPath('a/b/c', '2', 2)
