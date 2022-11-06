{
  "targets": [
    {
      "target_name": "valveLZSS",
      "sources": [
        "src/valveLZSS.cpp",
        "src/clzss.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags": [
        "-fPIC",
        "-ldl",
        "-lstdc++"
      ]
    }
  ]
}