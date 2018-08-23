# -*- coding:utf-8 -*-
__author__ = 'Threedog'
__Date__ = '2018/8/14 19:43'

import socket
import json
import threading

players = []


def recv_sockdata(the_socket):
    '''从网络接收数据'''
    total_data = ""
    while True:
        data = the_socket.recv(1024).decode()
        if "END" in data:
            # 注意这里不去掉末尾的END，直接转发给另一端
            total_data += data[:data.index("END")]
            break
        total_data += data
        # 如果超过了一定数量仍然没有检测到END，说明之前的数据全部失效
        if len(total_data) >= 10240:
            total_data = ""
    return total_data


def broadcast(data):
    '''
    向所有玩家广播信息
    '''
    for player in players:
        player.sock.sendall((json.dumps(data)+" END").encode())


def broadcast_refresh():
    '''
    向所有玩家广播玩家列表信息
    '''
    data = {"msg": "player_list", "data": [player.name for player in get_player_in_room()]}
    broadcast(data)


def get_player_by_name(name):
    '''
    通过名称获取用户
    '''
    for player in players:
        if player.name == name:
            return player

    return False


def get_player_in_room():
    '''
    返回所有在列表中的数据
    '''
    list = []
    for player in players:
        if player.state:
            list.append(player)
    return list


class Player(object):

    def __init__(self,sock,name):
        self.sock = sock  # 本地的sock
        self.name = name
        self.target_sock = None  # 联机对方的sock
        self.state = False  # 默认情况下没有加入到列表中
        # 启动线程监听
        threading.Thread(target=self.recv_data).start()

    def deal_data(self,json_data):
        '''数据处理'''
        print("data in server: ", json_data)
        if json_data['msg'] == 'refresh':  # 刷新玩家列表
            print("返回列表数据")
            data = {"msg": "player_list", "data": [player.name for player in get_player_in_room()]}
            self.sock.sendall((json.dumps(data) + " END").encode())
            data = {"msg": "get_name", "data": self.name}
            self.sock.sendall((json.dumps(data) + " END").encode())

        elif json_data['msg'] == 'battle':  # 选择玩家进行对战
            # 如果选择的对手是自己，则返回消息
            if json_data['data'] == self.name:
                data = {"msg":"replay","type":"battle","data":False,"info":"对局创建失败，请不要选择自己作为对手"}
                self.sock.sendall((json.dumps(data) + " END").encode())
                return
            target_player = get_player_by_name(json_data['data'])
            if target_player:
                self.target_sock = target_player.sock
                # 发给对手
                data = {"msg": "replay", "type": "battle", "data": True,"name":self.name}
                self.target_sock.sendall((json.dumps(data) + " END").encode())
                # 发给发起方
                data = {"msg": "replay", "type": "battle", "data": True,"name": target_player.name}
                target_player.target_sock = self.sock
                self.sock.sendall((json.dumps(data) + " END").encode())
            else:
                data = {"msg": "replay", "type": "battle", "data": False,"info":"对局创建失败，对方可能已经离线，请刷新列表后重试"}
                self.sock.sendall((json.dumps(data) + " END").encode())

        elif json_data['msg'] == "join":  # 玩家加入房间
            print(json_data['data'])
            print([player.name for player in get_player_in_room()])
            if json_data['data'] in [player.name for player in get_player_in_room()]:
                data = {"msg":"replay","type":"join","data":"该用户名已经存在，请更换昵称重试"}
                self.sock.sendall((json.dumps(data) + " END").encode())
                return
            self.name = json_data['data']
            self.state = True
            broadcast_refresh()  # 向所有玩家广播列表数据

        elif json_data['msg'] == "quit":  # 退出房间
            self.state = False
            broadcast_refresh()

    def recv_data(self):
        while True:
            try:
                res_data = recv_sockdata(self.sock)     # 本地收到数据
                json_data = json.loads(res_data)        # 转成json
                print(json_data)
                if json_data['target'] == 'player':     # 目标是玩家
                    if self.target_sock is not None:
                        print("data to player: ", json_data)
                        self.target_sock.sendall((json.dumps(json_data)+" END").encode())  # 发送给另一玩家
                elif json_data['target'] == 'server':   # 目标是服务器
                    self.deal_data(json_data)           # 交由本地解析器处理

            except (ConnectionAbortedError,ConnectionResetError):
                print("连接断开，玩家离开游戏")
                if self in players :
                    players.remove(self)
                    broadcast_refresh()
                break  # 退出循环，线程结束

            except json.JSONDecodeError:
                print("数据解析错误")
                print("Error Data:",res_data)
            # 在线程处理函数中不能直接进行界面的相关操作，所以用一个信号把数据发送出来
            # self.dataSignal.emit(data)
            # self.deal_data(data,parent)


def start_listen(server_sock):
    print("accepting!")
    while True:
        try:
            # 接受一个新连接:
            sock, addr = server_sock.accept()
            # 给新连接发送当前的列表信息
            data = {"msg":"player_list","data":[player.name for player in players]}
            sock.sendall((json.dumps(data) + " END").encode())
            # 接收新连接的用户名，创建类并放入玩家列表
            # dt = json.loads(sock.recv(1024).decode())
            # {"msg": "name", "data": self.name}
            # print(dt)
            # name = "未命名"
            # if dt['msg'] == 'name':
            #     name = dt['data']
            #     判断名字是否已经存在
                # if name in [p.name for p in players]:
                #     data = {"msg":"replay","data":"已经存在同名用户，请更换其他的用户名"}
                #     sock.sendall((json.dumps(data) + " END").encode())
                #     continue
            name="玩家{}".format(len(players))
            player = Player(sock,name)
            players.append(player)
            data = { "msg": "get_name", "data": name }
            sock.sendall((json.dumps(data) + " END").encode())

        except OSError:
            print("监听失败，socket已经失效")
            break


if __name__ == "__main__":
    tcp_server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    try:
        tcp_server.bind(('0.0.0.0', 3003))
        # 监听端口，传入的参数指定等待连接的最大数量
        tcp_server.listen(32)
    except OSError as e:
        print("监听失败：" + str(e))
        print("3003 端口被占用中，请关闭其他程序后重试。")

    # 线程监听，等待连接
    threading.Thread(target=start_listen,args=(tcp_server,)).start()


# class NetworkServer(NetworkPlayer):
#     '''
#     服务器类
#     '''
#     def __init__(self,name,parent=None):
#         super().__init__(name=name,parent=parent)
#
#         # 我是主机
#         print('我是主机')
#         # 创建Socket
#         self.tcpServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#         # 绑定地址
#         try:
#             self.tcpServer.bind(('0.0.0.0', 3003))
#         except OSError as e:
#             print("监听失败："+ str(e))
#             QMessageBox.question(self,"监听失败","端口被占用，请关闭其他程序后点击开始按钮重试")
#             print("3003 端口被占用中，请关闭其他程序后点击开始按钮重试。")
#             self.label_statuvalue.setText("监听失败,\n点开始重试")
#             return
#         # 监听端口，传入的参数指定等待连接的最大数量
#         self.tcpServer.listen(1)
#         # 线程监听，等待连接
#         threading.Thread(target=self.start_listen).start()
#
#     def start_listen(self):
#         print("accepting!")
#         while True:
#             try:
#                 self.is_listening = True
#                 self.label_statuvalue.setText("等待连接")
#                 # 接受一个新连接:
#                 sock, addr = self.tcpServer.accept()
#                 self.label_statuvalue.setText("连接成功,\n点击开始")
#                 # self.is_listening = False
#                 self.tcp_socket = sock
#                 # 连接成功后先向对方发送昵称信息
#                 data = {"msg": "name", "data": self.name}
#                 self.tcp_socket.sendall((json.dumps(data) + " END").encode())
#                 # 启动一个死循环处理数据，如果对方断开连接，会进行循环监听下次一客户端的连接
#                 self.recv_data(sock,addr)
#             except OSError:
#                 print("监听失败，socket已经失效")
#                 break
#
#     def restart(self):
#         # 监听失败的情况
#         if self.is_listening == False:
#             # 绑定地址
#             try:
#                 self.tcpServer.bind(('0.0.0.0', 3003))
#             except OSError as e:
#                 print("监听失败：" + str(e))
#                 QMessageBox.question(self, "监听失败", "端口被占用，请关闭其他程序后点击开始按钮重试")
#                 print("3003 端口被占用中，请关闭其他程序后点击开始按钮重试。")
#                 self.label_statuvalue.setText("监听失败,\n点开始重试")
#                 return
#             # 监听端口，传入的参数指定等待连接的最大数量
#             self.tcpServer.listen(1)
#             # 线程监听，等待连接
#             threading.Thread(target=self.start_listen).start()
#
#         # 连接尚未成功
#         if self.is_connected == False:
#             QMessageBox.information(self,"提示","对手尚未上线，请稍候")
#             return
#         else:
#             data = {"msg":"action","data":"restart"}
#             self.tcp_socket.sendall((json.dumps(data) + " END").encode())
#             self.label_statuvalue.setText("等待开始")
#
#     def closeEvent(self, a0: QCloseEvent):
#         if self.is_connected:
#             self.tcp_socket.sendall((json.dumps({"msg": "action", "data": "exit"})).encode())
#             self.tcp_socket.close()
#             self.is_connected = False
#         if self.is_listening:
#             self.tcpServer.close()
#             self.is_listening = False
#         return super().closeEvent(a0)
#
#
#
#
