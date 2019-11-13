using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace PPD_Lab5
{
    class Program
    {
        static void DownloadWithCallbacks(string[] websites)
        {
            var downloaders = new List<CallbackDownloader>();

            foreach (var website in websites)
            {
                var downloader = new CallbackDownloader(website);
                downloaders.Add(downloader);
                downloader.DownloadPage();
            }

            foreach (var downloader in downloaders)
            {
                downloader.Wait();
            }
        }
        
        static void DownloadWihTasks(string[] websites)
        {
            var downloaders = new List<Task>();

            foreach (var website in websites)
            {
                var downloader = new TaskDownloader(website);
                downloaders.Add(Task.Factory.StartNew(downloader.DownloadPage));
            }

            Task.WaitAll(downloaders.ToArray());
        }
        
        static void DownloadWihAsync(string[] websites)
        {
            var downloaders = new List<Task>();

            foreach (var website in websites)
            {
                var downloader = new AsyncDownloader(website);
                downloaders.Add(Task.Factory.StartNew(downloader.DownloadPage));
            }

            Task.WaitAll(downloaders.ToArray());
        }
        
        static void Main(string[] args)
        {
            string[] websites =
            {
                "www.cs.ubbcluj.ro/~motogna/LFTC/LAB5.txt","www.cs.ubbcluj.ro/~motogna/LFTC/LAB4.txt",
                "www.cs.ubbcluj.ro/~motogna/LFTC/lab3.txt", "www.cs.ubbcluj.ro/~motogna/LFTC/lab2.txt",
                "www.cs.ubbcluj.ro/~motogna/LFTC/lab1.txt"
            };

            //DownloadWithCallbacks(websites);
            //DownloadWihTasks(websites);
            DownloadWihAsync(websites);
        }
    }
}