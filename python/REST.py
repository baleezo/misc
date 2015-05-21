#!/usr/bin/env python
import cjson

def rest_path_to_json(path, update_data, root_level):
    splitted_path = path.strip('/').split('/')
    path_len = len(splitted_path)
    f_update_data = update_data

    if path_len < root_level:
        print 'Update path error [%s] too short' %path
        return splitted_path, cjson.decode(f_update_data)

    if path_len == root_level:
        try:
            return splitted_path, cjson.decode(f_update_data)
        except:
            return splitted_path, '{}'

    f_update_data = []
    for i in xrange(root_level, path_len):
        f_update_data.append('{"')
        f_update_data.append(splitted_path[i])
        f_update_data.append('":')

    if isinstance(update_data, str) and '"' not in update_data:
        update_data = ''.join(['"', update_data, '"'])

    f_update_data.append(update_data)

    for i in xrange(root_level, path_len):
        f_update_data.append('}')

    f_update_data = ''.join(f_update_data)
    try:
        f_update_data = cjson.decode(f_update_data)
    except Exception as e:
        print 'error', e
        f_update_data = {}

    return splitted_path, f_update_data


def run_test(path, data, r_level):
    s_path, u_data = rest_path_to_json(path, data, r_level)
    print 'translate path [', path, '] with data [', data, '] and root level [', r_level, '] to', u_data

if __name__ == '__main__':
    run_test('a/b/c/d/f/g/h', '{2:{3:4}}', 2)
