# LS PLC MASTER K120s  modbus    
[김동일교수 유튜브보기](http://i2r.link)

### 2-27-1 node red program
node red로 plc 프로토콜을 만들어 입력을 모니터링 하고 출력을 제어한다.     
````
[
    {
        "id": "81c4951e7d906372",
        "type": "debug",
        "z": "0981fdccc9de072a",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 350,
        "y": 100,
        "wires": []
    },
    {
        "id": "e2043b637b724e4a",
        "type": "serial in",
        "z": "0981fdccc9de072a",
        "name": "",
        "serial": "63957752.49a888",
        "x": 210,
        "y": 100,
        "wires": [
            [
                "81c4951e7d906372"
            ]
        ]
    },
    {
        "id": "94b94c351050a97c",
        "type": "serial out",
        "z": "0981fdccc9de072a",
        "name": "",
        "serial": "63957752.49a888",
        "x": 670,
        "y": 180,
        "wires": []
    },
    {
        "id": "fb3dccaf0d4f6c74",
        "type": "function",
        "z": "0981fdccc9de072a",
        "name": "modbus cal",
        "func": "var auchCRCHi = [\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40\n      ];\n\n      /* Table of CRC values for low-order byte */\n    var auchCRCLo = [\n        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,\n        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,\n        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,\n        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,\n        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,\n        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,\n        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,\n        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,\n        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,\n        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,\n        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,\n        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,\n        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,\n        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,\n        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,\n        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,\n        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,\n        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,\n        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,\n        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,\n        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,\n        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,\n        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,\n        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,\n        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,\n        0x43, 0x83, 0x41, 0x81, 0x80, 0x40\n      ];\n\nvar nTemp;\nvar wCRCWord = 0xFFFF;\ndata=msg.payload;\nvar len=msg.payload.length-2;\nvar crc = [0xFF, 0xFF];\n    var nextByte = 0;\n    var uIndex; /* will index into CRC lookup*/ /* table */\n    /* pass through message buffer */\n    for (var i = 0; i < len && i < data.length; i++) {\n      nextByte = 0xFF & (data[i]);\n      uIndex = crc[0] ^ nextByte; //*puchMsg++; /* calculate the CRC */\n      crc[0] = crc[1] ^ auchCRCHi[uIndex];\n      crc[1] = auchCRCLo[uIndex];\n    }\n\ndata[len]=crc[0];\ndata[len+1]=crc[1];\nmsg.payload= data;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 490,
        "y": 180,
        "wires": [
            [
                "94b94c351050a97c"
            ]
        ]
    },
    {
        "id": "b72de589a7ebb03d",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "출력 비트 읽기-1",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,1,0,64,0,20,0,0]",
        "payloadType": "bin",
        "x": 260,
        "y": 180,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "029e5100d4214ca0",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 개별 쓰기 on - 5",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,5,0,64,255,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 280,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "8d25fc94e1dc2e53",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 개별 쓰기 off - 5",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,5,0,64,0,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 320,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "7ca472d76232538a",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "워드 개별 쓰기 - 6",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,6,0,4,0,255,0,0]",
        "payloadType": "bin",
        "x": 270,
        "y": 360,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "e269778788d668a5",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 연속 쓰기 on - 15",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,15,0,64,0,10,2,255,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 460,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "ff0ea8ef1ddd9ba7",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 연속 쓰기 off - 15",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,15,0,64,0,10,2,0,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 500,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "5910fdc2a33f074b",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "입력 비트 읽기-2",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,2,0,0,0,20,0,0]",
        "payloadType": "bin",
        "x": 260,
        "y": 220,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "2ac63ca411b4adef",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "워드 개별 쓰기 - 6",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,6,0,4,0,0,0,0]",
        "payloadType": "bin",
        "x": 270,
        "y": 400,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "63957752.49a888",
        "type": "serial-port",
        "serialport": "COM6",
        "serialbaud": "19200",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "100",
        "bin": "bin",
        "out": "time",
        "addchar": "",
        "responsetimeout": "10000"
    }
]
````

